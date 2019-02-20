


#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <cmath> //abs
#include <limits.h>
#include "poly.h"

using namespace std;
namespace coen79_lab4{
    /* contructor */
    polynomial::polynomial(double c, unsigned int exponent){
        assert(exponent<=MAXIMUM_DEGREE);
        coefs[exponent]=c;
        
    }
    
    /* MODIFICATION MEMBER FUNCTIONS */
    
    //helper functions
    //sets degree of function to correct highest degree of the polynomial
    void polynomial::update_current_degree(){
        //runs from high to low to look fro highest non-zero coefficient
        for(int i=MAXIMUM_DEGREE; i>0; i--){
            fdegree = 0;
            if(coefs[i]!=0.0){
                fdegree = i;
                return; //when degree is found, return is forced to end for loop
            }
        }
    }
    
    //sets the coefficient of the the given exponent
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
        assert(exponent<=MAXIMUM_DEGREE);
        coefs[exponent]=coefficient;
        update_current_degree();
        
    }
    
    //adds given amount to specified coefficient
    void polynomial::add_to_coef(double amount, unsigned int exponent){
        assert(exponent<=MAXIMUM_DEGREE);
        coefs[exponent] += amount;
        update_current_degree();
    }
    
    //sets all coeficients to zero
    void polynomial::clear(){
        for(int i=0; i<=MAXIMUM_DEGREE; i++){
            coefs[i]=0.0;
            fdegree = 0;
        }
    }
    
    /* CONSTANT MEMEBER FUNCTIONS */
    
    //returns a polynomial that is the indefinite integral
    //with the value of the constant at zero
    polynomial polynomial::antiderivative() const{
        assert(this->degree() < MAXIMUM_DEGREE);
        polynomial anti = *this;
        //shifts all coefficients to the right one
        //and divides by exponent i+1
        for(int i=1; i<=MAXIMUM_DEGREE;i++){
            anti.assign_coef((coefs[i-1]/i), i);
        }
        anti.assign_coef(0.0, 0);
        return anti;
    }
    
    //returns coefficent at given exponent
    double polynomial::coefficient(unsigned int exponent) const{
        if(exponent < MAXIMUM_DEGREE)
            return coefs[exponent];
        else
            return 0.0;
    }
    
    //returns the definite integral
    double polynomial::definite_integral(double x0, double x1) const{
        polynomial integral = this->antiderivative();
        return ( integral.eval(x1)-integral.eval(x0) );
    }
    
    //double cheks the degree is correct and returns the degree
    unsigned int polynomial::degree() const{
        return fdegree;
    }
    
    //returns a polynomial thats a derivative of the current polynomial
    polynomial polynomial::derivative() const{
        polynomial deriv = *this;
        //shifts all coefficients to the left one
        //and multiplies by exponent i+1
        for(int i=0; i<MAXIMUM_DEGREE;i++){
            deriv.assign_coef(((coefs[i+1])*(i+1)), i);
        }
        deriv.assign_coef(0, MAXIMUM_DEGREE);
        return deriv;
    }
    
    //returns value of polynomial when evaluated with x
    double polynomial::eval(double x) const{
        double total = 0;
        for(int i=0; i<=MAXIMUM_DEGREE;i++){
            total+=(coefs[i]*pow(x,i));
            //calculates each term and adds to total variable
        }
        return total;
    }
    
    //returns true if all coefficients are zero
    bool polynomial::is_zero() const{
        //degree() makes sure the degree is up to date
        if(degree()==0)
            return true;
        else
            return false;
        
    }
    
    //returns exponent > e that has a non-zero coefficient
    unsigned int polynomial::next_term(unsigned int e) const{
        for(int i=e+1; i<=MAXIMUM_DEGREE; i++){
            if(coefs[i]!=0)
                return i;
        }
        return 0;
    }
    
    unsigned int polynomial::previous_term(unsigned int e) const{
        for(int i=e-1; i>=0; i--){
            if(coefs[i]!=0)
                return i;
        }
        return UINT_MAX;
    }
    
    double polynomial::operator() (double x) const{
        return eval(x);
    }
    
    /* NON-MEMBER OPERATORS */
    
    //returns a polynomial where its coefficients are the
    //addition of the coefficients of the pssed polynomials
    polynomial operator +(const polynomial &p1, const polynomial &p2){
        polynomial poly = polynomial(p1);
        for(int i=0; i<=polynomial::MAXIMUM_DEGREE; i++){
            poly.add_to_coef(p2.coefficient(i), i);
        }
        return poly;
    }
    
    //returns a polynomial where its coefficients are the
    //subtraction of the coefficients of the pssed polynomials
    polynomial operator -(const polynomial &p1, const polynomial &p2){
        polynomial poly = polynomial(p1);
        for(int i=0; i<=polynomial::MAXIMUM_DEGREE; i++){
            poly.add_to_coef(-1*p2.coefficient(i), i);
        }
        return poly;
    }
    
    
    polynomial operator *(const polynomial &p1, const polynomial &p2){
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        polynomial poly;
        for(int i=0; i<=p1.degree();i++) {
            for(int j=0; j<=p2.degree(); j++){
                poly.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j);
                //adds the multiplication of two coefficients at position
                //of the sum of their exponents
            }
        }
        return poly;
        
        
    }
    
    /* NON-MEMBER OUTPUT FUNCTIONS */
    ostream &operator <<(ostream &out, const polynomial &p){
        if (p.degree()==1){
            cout<<p.coefficient(1)<<"x";
        }
        else if (p.degree()==0){
            cout<<p.coefficient(0);
        }
        else{
            cout<<p.coefficient(p.degree())<<"x^"<<p.degree();

        }
        
        for(int i=p.degree()-1; i>1; i--){
            if (p.coefficient(i)>0){
                cout<<" + "<<p.coefficient(i)<<"x^"<<i;
            }
            else if (p.coefficient(i)<0){
                cout<<" - "<<abs(p.coefficient(i))<<"x^"<<i;
            }
        }
        
        //for 1 exponent case
        if (p.degree()>1 && p.coefficient(1)>0){
            cout<<" + "<<p.coefficient(1)<<"x";
        }
        else if (p.degree()>1 && p.coefficient(1)<0){
            cout<<" - "<<abs(p.coefficient(1))<<"x";
        }
        
        //for 0 exponet case
        if (p.degree()>0 && p.coefficient(0)>0){
            cout<<" + "<<p.coefficient(0);
        }
        else if (p.degree()>0 && p.coefficient(0)<0){
            cout<<" - "<<abs(p.coefficient(0));
        }

        out<<endl;
        
        
        return out;
    }
    
    
    
    
    
}
