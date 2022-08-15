#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
const double PI = 3.14159265;

using namespace std;

struct Vector{
    double x;
    double y;
    double z;
};

void print_vector(const Vector V){
    cout<< V.x <<" "<< V.y <<" "<< V.z<< endl;
}

Vector sum(const Vector v1, const Vector v2){
    Vector C;
    C.x= v1.x+v2.x;
    C.y= v1.y+v2.y;
    C.z= v1.z+v2.z;

    return C;
}

Vector diff(const Vector v1, const Vector v2){
    Vector C;
    C.x= v1.x-v2.x;
    C.y= v1.y-v2.y;
    C.z= v1.z-v2.z;

    return C;
}

double dot_product(const Vector v1, const Vector v2){
    double C;

	C=v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;

	return C;
}

Vector cross_product(const Vector v1, const Vector v2){
	Vector C;
	C.x=(v1.x*v2.y-v1.y*v2.x);
	C.y=(v1.x*v2.z-v1.z*v2.x);
	C.z=(v1.y*v2.z-v1.z*v2.y);

	return C;
}

double norm(const Vector v){
	double M,N;
	M=(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
	N=sqrt(M);

	return N;
}

int is_unitvector(const Vector v){
	int m;
	m= sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));

	return m;
}

Vector unit(const Vector v){
	Vector C;
	
	C.x=v.x/norm(v);
	C.y=v.y/norm(v);
	C.z=v.z/norm(v);
	
	return C;
}

Vector multiplyby_scalar(const Vector v1, const double c){
	
	Vector M;
	M.x=v1.x*c;
	M.y=v1.y*c;
	M.z=v1.z*c;

	return M;
	 
}

double angle(const Vector v1, const Vector v2){
	double n,m,a,b;
	a=dot_product(v1,v2);
	b=norm(v1)*norm(v2);
	n=a/b;
	m=acos(n);
	
	
	return m;
}

double distance(const Vector v1, const Vector v2){
	double a,b,c,N;
	a=v1.x-v2.x;
	b=v1.y-v2.y;
	c=v1.z-v2.z;
	N=pow(a,2)+pow(b,2)+pow(c,2);
	N=sqrt(N);

	return N;
}

int are_linearly_independent(const Vector v1, const Vector v2, const Vector v3){
	double N;
	N=(v1.x*v2.y*v3.z)+(v2.x*v3.y*v1.z)+(v3.x*v1.y*v2.z)-(v1.z*v2.y*v3.x)-(v2.z*v3.y*v1.x)-(v3.z*v1.y*v2.x);

	return N;
}
 
int are_orthogonal(const Vector v1, const Vector v2, const Vector v3){
	if(dot_product(v1,v2)==0&&dot_product(v1,v3)==0&&dot_product(v2,v3)==0){
		return 1;
	}
	else return 0;
}

int are_orthonormal(const Vector v1, const Vector v2, const Vector v3){
	if(are_orthogonal(v1,v2,v3)==1&&is_unitvector(v1)==1&&is_unitvector(v2)==1&&is_unitvector(v3)==1) return 1;
	else return 0;
}

Vector projection(const Vector v1, const Vector v2){
	Vector C;
	C.x=(dot_product(v1,v2)/pow(norm(v2),2))*v2.x;
	C.y=(dot_product(v1,v2)/pow(norm(v2),2))*v2.y;
	C.z=(dot_product(v1,v2)/pow(norm(v2),2))*v2.z;

	return C;
}

Vector orthogonal_projection(const Vector v1, const Vector v2){
	Vector C;
	C.x= v1.x- (projection(v1,v2).x);
	C.y= v1.y- (projection(v1,v2).y);
	C.z= v1.z- (projection(v1,v2).z);

	return C;
}

int convert_2_orthogonal_basis(Vector *v1, Vector *v2, Vector *v3){
	Vector A=*v1,B=*v2,C=*v3;
	v2->x=v2->x-projection(B,A).x;
	v2->y=v2->y-projection(B,A).y;
	v2->z=v2->z-projection(B,A).z;
	
	v3->x=v3->x- projection(C,A).x-projection(C,*v2).x;
	v3->y=v3->y- projection(C,A).y-projection(C,*v2).y;
	v3->z=v3->z- projection(C,A).z-projection(C,*v2).z;
	
	if( are_linearly_independent(*v1,*v2,*v3)!=0) return 1;
	else return 0;
}

char* vector2str(const Vector v){
	char *S[80];

	sprintf(*S,"(%.2f %.2f %.2f)",v.x,v.y,v.z);
	
	return *S;
	
}

int main(){
    double k=2;
    Vector v1 = {1, 2, 2}, v2 = {-1, 0, 2}, v3 = {0, 0, 1};

    cout<<"1. Vektor: ";
    print_vector(v1);
    cout<<"2. Vektor: ";
    print_vector(v2);
    cout<<"3. Vektor: ";
    print_vector(v3);

    cout<<"Vektor 1 + Vektor 2: ";
    print_vector(sum(v1,v2));
   
    cout<<"Vector 1 - Vektor 2: ";
    print_vector(diff(v1,v2));

    cout<<"Vector 1 . Vektor 2: ";
    cout<<dot_product(v1,v2)<<endl;

    cout<<"Vector 1 x Vektor 2: ";
    print_vector(cross_product(v1,v2));

    cout<<"|v1|= ";
    cout<<(norm(v1))<<endl;

    cout<<"|v2|= ";
    cout<<(norm(v2))<<endl;

    if(is_unitvector(v1)==1)
		cout<<"v1 is an unit vector"<<endl;
	else
		cout<<"v1 is not an unit vector"<<endl;

    cout<<"Unit of v1:";
    print_vector(unit(v1));

    cout<<"k*v1=";
    print_vector(multiplyby_scalar(v1,k));

    cout<<"angle v1 and v2=";
    cout<<(angle(v1,v2))<<endl;

    cout<<"distance of v1 and v2=";
    cout<<(distance(v1,v2))<<endl;

    if(are_linearly_independent(v1, v2, v3)!=0)
		cout<<"Vectors are linearly independent."<<endl;
	else
		cout<<"Vectors are not linearly independent."<<endl;

    if(are_orthogonal(v1, v2, v3)==1)
		cout<<"Vectors are orthogonal."<<endl;
	else
		cout<<"Vectors are not orthogonal."<<endl;	
		
	if(are_orthonormal(v1, v2, v3)==1)
		cout<<"Vectors are orthonormal."<<endl;
	else
		cout<<"Vectors are not orthonormal."<<endl;

    cout<<"Projection of v1 onto v2 is = ";
    print_vector(projection(v1,v2));

    cout<<"Orthogonal projection of v1 onto v2 is = ";
    print_vector(orthogonal_projection(v1,v2));

    if(convert_2_orthogonal_basis(&v1, &v2, &v3)==1){
		cout<<"Orthogonalization of vectors:"<<"\n"<<"v1= ";
	    print_vector(v1);

        cout<<"v2= ";
	    print_vector(v2);

        cout<<"v3= ";
	    print_vector(v3);
	}		
	
	puts(vector2str(v1));
	
	  return 0;


}