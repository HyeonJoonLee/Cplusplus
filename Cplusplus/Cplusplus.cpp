#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream> // C++ 입출력 함수 사용
#include <string>   // C++ 문자열 사용
//타입 선언
typedef struct { int degree;  float coef[100]; } poly1;
typedef struct { float coef;  int exp; } poly2;
typedef struct poly3 { float coef; int exp; struct poly3* link; }poly3;
typedef struct student
{
	int no;
	char name[10];
	int k, e, m, tot;
	float ave;

}student;
typedef struct student2
{
	int no;
	char name[10];
	int k, e, m, tot;
	float ave;
	struct student2* link; //다음 구조체의 주소를 저장하는 멤버

}student2;

//함수 선언
void score(int k[], int e[], int m[], int t[], float a[])
{
	for (int i = 0; i < 3; i++)
	{
		t[i] = k[i] + e[i] + m[i];
		a[i] = t[i] / 3.0;
	}
}
//다항식 덧셈하는 함수
void add(poly1* PA, poly1* PB, poly1* PC)
{
	int deg_A, deg_B;
	int Apos, Bpos, Cpos;
	Apos = Bpos = Cpos = 0;
	deg_A = PA->degree;  deg_B = PB->degree;

	if (deg_A > deg_B) PC->degree = deg_A;
	else               PC->degree = deg_B;

	while (Apos <= PA->degree && Bpos <= PB->degree)
	{
		if (deg_A > deg_B)
		{
			PC->coef[Cpos++] = PA->coef[Apos++];
			deg_A--;
		}
		else if (deg_A < deg_B)
		{
			PC->coef[Cpos++] = PB->coef[Bpos++];
			deg_B--;
		}
		else //차수가 같을 때
		{
			PC->coef[Cpos++] = PA->coef[Apos++] + PB->coef[Bpos++];
			deg_A--; deg_B--;
		}
	}
}

//다항식 뺄셈하는 함수
void sub(poly1* PA, poly1* PB, poly1* PD)
{
	int deg_A, deg_B;
	int Apos, Bpos, Dpos;
	Apos = Bpos = Dpos = 0;
	deg_A = PA->degree;  deg_B = PB->degree;

	if (deg_A > deg_B) PD->degree = deg_A;
	else               PD->degree = deg_B;

	while (Apos <= PA->degree && Bpos <= PB->degree)
	{
		if (deg_A > deg_B)
		{
			PD->coef[Dpos++] = PA->coef[Apos++];
			deg_A--;
		}
		else if (deg_A < deg_B)
		{
			PD->coef[Dpos++] = -PB->coef[Bpos++];
			deg_B--;
		}
		else //차수가 같을 때
		{
			PD->coef[Dpos++] = PA->coef[Apos++] - PB->coef[Bpos++];
			deg_A--; deg_B--;
		}
	}
}

void calc(poly2 p[])
{
	int i, n;
	int As, Bs, Cs, Ae, Be;
	//입력
	std::cout << "다항식 A의 항 계수 : ";
	std::cin >> n;

	As = 0, Ae = As + n - 1;
	for (i = As; i <= Ae; i++)
		scanf_s("%f %d", &p[i].coef, &p[i].exp);

	std::cout << "다항식 B의 항 계수 : ";
	std::cin >> n;

	Bs = Ae + 1, Be = Bs + n - 1;
	for (i = Bs; i <= Be; i++)
		scanf_s("%f %d", &p[i].coef, &p[i].exp);

	Cs = Be + 1;
	//호출(계산)
	while (1)
	{
		if (As > Ae || Bs > Be)
			break;

		if (p[As].exp == p[Bs].exp) //비교되는 항의 차수가 같냐
		{ //A의 계수 + B의 계수 --> C의 계수에 복사(차수도 복사) As,Bs,Cs 증가
			if (p[As].coef + p[Bs].coef == 0)
			{ //계수의 합이 0이면 저장 안함
				As++;
				Bs++;
			}
			else
			{
				p[Cs].coef = p[As].coef + p[Bs].coef;
				p[Cs].exp = p[As].exp;
				As++;
				Bs++;
				Cs++;
			}
		}
		else if (p[As].exp > p[Bs].exp) //A의 차수가 더 크냐
		{ //A의 계수, 차수를 C에 복사 --> As, Cs 증가
			p[Cs].coef = p[As].coef;
			p[Cs].exp = p[As].exp;
			As++;
			Cs++;
		}
		else//B의 차수가 더 크냐
		{ //B의 계수, 차수를 C에 복사 --> Bs, Cs 증가
			p[Cs].coef = p[Bs].coef;
			p[Cs].exp = p[Bs].exp;
			Bs++;
			Cs++;
		}
	}// while문 끝

	if (As > Ae) //다항식 B의 항이 남았다.
		for (i = Bs; i <= Be; i++)
		{
			p[Cs].coef = p[Bs].coef;
			p[Cs].exp = p[Bs].exp;
			Bs++;
			Cs++;
		}
	else if (Bs > Be) // 다항식 A의 항이 남았다.
		for (i = As; i <= Ae; i++)
		{
			p[Cs].coef = p[As].coef;
			p[Cs].exp = p[As].exp;
			As++;
			Cs++;
		}

	//출력
	std::cout << "\n다항식 A = ";
	for (i = 0; i <= Ae; i++)
		printf("%6.1f X %d", p[i].coef, p[i].exp);

	std::cout << "\n다항식 B = ";
	for (i = Ae + 1; i <= Be; i++)
		printf("%6.1f X %d", p[i].coef, p[i].exp);

	std::cout << "\n다항식 C = ";
	for (i = Be + 1; i <= Cs - 1; i++)
		printf("%6.1f X %d", p[i].coef, p[i].exp);

}

void score2(student sss[])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		sss[i].tot = sss[i].k + sss[i].e + sss[i].m;
		sss[i].ave = sss[i].tot / 3.0;
	}
}

poly3* link_add(poly3* X, poly3* Y, poly3* Z) //연결구조체를 이용한 다항식 덧셈 함수
{
	poly3* p, * q, * r, * r2;
	p = X, q = Y;
	r = (poly3*)malloc(sizeof(struct poly3));
	Z = r2 = r;

	while (1)
	{
		if (p == NULL || q == NULL) break;

		if (p->exp == q->exp) //차수가 같으면?
		{
			if (p->coef + q->coef != 0)
			{
				r->coef = p->coef + q->coef;
				r->exp = p->exp;
				r->link = NULL;
				r2->link = r;
				r2 = r;
				r = (poly3*)malloc(sizeof(struct poly3));
			}
			p = p->link; q = q->link;
		}
		else if (p->exp > q->exp) // 다항식 X의 차수가 더 크면?
		{
			r->coef = p->coef;
			r->exp = p->exp;
			r->link = NULL;
			r2->link = r;
			r2 = r;
			r = (poly3*)malloc(sizeof(struct poly3));
			p = p->link;
		}
		else if (p->exp < q->exp) // 다항식 Y의 차수가 더 크면?
		{
			r->coef = q->coef;
			r->exp = q->exp;
			r->link = NULL;
			r2->link = r;
			r2 = r;
			r = (poly3*)malloc(sizeof(struct poly3));
			q = q->link;
		}
	}
	// while문 끝 -> 남은 항들을 Z에 붙여넣기
	if (p == NULL)
	{
		while (q != NULL)
		{
			r->coef = q->coef;
			r->exp = q->exp;
			r->link = NULL;
			r2->link = r;
			r2 = r;
			r = (poly3*)malloc(sizeof(struct poly3));
			q = q->link;
		}
	}
	else if (q == NULL)
	{
		while (p != NULL)
		{
			r->coef = p->coef;
			r->exp = p->exp;
			r->link = NULL;
			r2->link = r;
			r2 = r;
			r = (poly3*)malloc(sizeof(struct poly3));
			p = p->link;
		}
	}
	return Z;
}

void main()
{
	int i, menu, n;
	//배열 7개 선언
	int no[3], k[3], e[3], m[3], t[3];
	float a[3];
	char name[3][10];

	//다항식 배열을 위한 선언
	poly1  A, B, C, D;
	poly2 p[100];
	//구조체를 성적처리하기 위한 구조체배열 변수 선언
	student st[3];
	student2* s, * P, * q;
	s = P = q = NULL;

	poly3* X, * Y, * Z, * a1, * b1, * c1, * c2;
	X = Y = Z = a1 = b1 = c1 = c2 = NULL;

	while (1) //무한루프
	{
		printf("\n\n\n 메뉴 1)성적처리(배열)  2)다항식-1 덧뺄셈  3)다항식-2 덧뺄셈 4)성적처리(구조체 배열) \n");
		printf("5)성적처리(연결 구조체) 6)다항식 덧뺄셈(연결구조체)  7)종료: ");
		scanf_s("%d", &menu);  if (menu == 7) break;
		switch (menu) {
		case 1://학번, 이름, 국,영,수 입력해서 총점/평균 계산후 출력
			printf("학번, 이름, 국, 영, 수 입력 \n");
			for (i = 0; i < 3; i++)
			{
				printf("\n 학번 : "); scanf_s("%d", &no[i]);
				printf("\n 이름 : "); std::cin >> name[i];
				printf("\n 국어 : "); scanf_s("%d", &k[i]);
				printf("\n 영어 : "); scanf_s("%d", &e[i]);
				printf("\n 수학 : "); scanf_s("%d", &m[i]);
				printf("\n");
			}
			score(k, e, m, t, a);
			printf("\n 학번, 이름, 국, 영, 수, 총점, 평균  \n");
			for (i = 0; i < 3; i++)
			{
				printf(" %3d %10s %3d %3d %3d %3d %5.1f \n",
					no[i], name[i], k[i], e[i], m[i], t[i], a[i]);
			}
			break;
		case 2://다항식 2개 입력, 계산, 결과 다항식 출력
			printf("\n 다항식 A의 차수 : "); scanf_s("%d", &A.degree);
			printf("\n 다항식 A의 계수 : ");
			for (i = 0; i <= A.degree; i++)
				scanf_s("%f", &A.coef[i]);
			printf("\n 다항식 B의 차수 : "); scanf_s("%d", &B.degree);
			printf("\n 다항식 B의 계수 : ");
			for (i = 0; i <= B.degree; i++)
				scanf_s("%f", &B.coef[i]);

			// 다항식 덧셈
			add(&A, &B, &C); //인수로 구조체 변수를 CBR 전달
			// 다항식 뺄셈
			sub(&A, &B, &D);

			//출력
			printf("\n 다항식 A = ");
			for (i = 0; i <= A.degree; i++)
				printf("%.1fX%d + ", A.coef[i], A.degree - i);
			printf("\n 다항식 B = ");
			for (i = 0; i <= B.degree; i++)
				printf("%.1fX%d + ", B.coef[i], B.degree - i);
			printf("\n 덧셈한 다항식 C = ");
			for (i = 0; i <= C.degree; i++)
				printf("%.1fX%d + ", C.coef[i], C.degree - i);
			printf("\n 뺄셈한 다항식 D = ");
			for (i = 0; i <= D.degree; i++)
				printf("%.1fX%d + ", D.coef[i], D.degree - i);
			break;
		case 3: //poly2 구조체를 이용하여 다항식 덧뺄셈 수행
			calc(p);
			break;
		case 4:
			printf("학번, 이름, 국, 영, 수 입력 \n");
			for (i = 0; i < 3; i++)
			{
				printf("\n 학번 : "); std::cin >> st[i].no;
				printf("\n 이름 : "); std::cin >> st[i].name;
				printf("\n 국어 : "); std::cin >> st[i].k;
				printf("\n 영어 : "); std::cin >> st[i].e;
				printf("\n 수학 : "); std::cin >> st[i].m;
				printf("\n");
			}
			score2(st);
			printf("\n 학번, 이름, 국, 영, 수, 총점, 평균  \n");
			for (i = 0; i < 3; i++)
			{
				printf(" %3d %3s %3d %3d %3d %3d %5.1f \n",
					st[i].no, st[i].name, st[i].k, st[i].e, st[i].m, st[i].tot, st[i].ave);
			}
			break;
		case 5://자기 참조 구조체로 성적처리
			P = (student2*)malloc(sizeof(student2));
			s = q = P;
			while (1)
			{
				printf("\n 학번 : "); std::cin >> P->no;
				if (P->no < 0)
					break;
				printf("\n 이름 : "); std::cin >> P->name;
				printf("\n 국어 : "); std::cin >> P->k;
				printf("\n 영어 : "); std::cin >> P->e;
				printf("\n 수학 : "); std::cin >> P->m;
				printf("\n");
				P->tot = P->k + P->e + P->m;
				P->ave = P->tot / 3.0;

				P->link = NULL;
				q->link = P;
				q = P;
				P = (student2*)malloc(sizeof(student2));
			}
			//출력
			P = s;
			while (1)
			{
				if (P == NULL)
					break;
				printf("\n\n %3d %3s %3d %3d %3d %3d %6.1f", P->no, P->name, P->k, P->e, P->m, P->tot, P->ave);

				P = P->link;
			}
			break;
		case 6://연결 구조체를 이용하여 다항식 덧뺄셈 하기
			//다항식 X 입력
			std::cout << "\n 다항식 A 입력(계수 차수 : 계수 -999 입력하면 종료)";
			a1 = (poly3*)malloc(sizeof(struct poly3));
			X = b1 = a1;
			while (1)
			{
				std::cout << "\n 계수 : "; std::cin >> a1->coef;
				if (a1->coef == -999) break;
				std::cout << "\n 차수 : "; std::cin >> a1->exp;
				a1->link = NULL;
				b1->link = a1;
				b1 = a1;
				a1 = (poly3*)malloc(sizeof(struct poly3));
			}
			//다항식 Y 입력
			std::cout << "\n 다항식 B 입력(계수 차수 : 계수 -999 입력하면 종료)";
			a1 = (poly3*)malloc(sizeof(struct poly3));
			Y = b1 = a1;
			while (1)
			{
				std::cout << "\n 계수 : "; std::cin >> a1->coef;
				if (a1->coef == -999) break;
				std::cout << "\n 차수 : "; std::cin >> a1->exp;
				a1->link = NULL;
				b1->link = a1;
				b1 = a1;
				a1 = (poly3*)malloc(sizeof(struct poly3));
			}
			//계산
			Z = link_add(X, Y, Z);

			//다항식 X 출력
			a1 = X;
			std::cout << "\n\n 다항식 A = ";
			while (1)
			{
				if (a1 == NULL) break;
				std::cout << a1->coef << "X" << a1->exp << " ";
				a1 = a1->link;

			}
			//다항식 Y 출력
			a1 = Y;
			std::cout << "\n\n 다항식 B = ";
			while (1)
			{
				if (a1 == NULL) break;
				std::cout << a1->coef << "Y" << a1->exp << " ";
				a1 = a1->link;

			}
			//다항식 Z 출력
			a1 = Z;
			std::cout << "\n\n 다항식 C = ";
			while (1)
			{
				if (a1 == NULL) break;
				std::cout << a1->coef << "Z" << a1->exp << " ";
				a1 = a1->link;

			}

			break;
		default: printf("\n 메뉴선택 오류. 다시 선택하시오...\n\n");
		}
	}
}