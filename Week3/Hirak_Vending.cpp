#include <iostream>
#include <string>
#include<cmath>
using namespace std;

int main(void) {


string e;
string s;
string b;
string i1;
string i2;
string i3;

cout << "For Lunch menu: Enter e1 = Veggie Burger = $7,   e2 = Falafel Wrap = $6, e3 = salami sandwich = $9: " << endl;
cout << "  " << endl;
cout << "For Side dishes: Enter s1 = French Fries = $2, s2 = Hummas with Pita chips = $3, s3 = Celery and Carrots = $2: "<< endl;
cout << "  " << endl;
cout << "For Beverages: Enter b1 = Tap water (free of cost!!), b2 = Sparkling water = $2, b3 = Domestic Beer = $4, b4 = Imported Beer = $6, b5 = Red Wine = $7, b6 = White Wine, b7 = Coffee = $1 and b8 = Tea = $1: "<< endl;
cout << "  " << endl;
cout << "You can order in any sequence. e.g. b1,e3,s2" << endl;
cout << "  " << endl;
cout << " Great News! Certain combinations are on special, so the price is discounted. A veggie burger and fries, plus any non-alcoholic drink (b1,b2,b7,b8) is $8. A Falafel wrap plus hummus with pita chips, and any hot beverage (Coffee or Tea) is $7. A salami sandwich with any side and any alcoholic beverage is $13." << endl;
cout << "  " << endl;
cout << "Enter your order, after each input press enter" << endl;
cin >> i1;
if (i1 == "e1" || i1 == "e2" || i1 == "e3") {
	e = i1;
	//cout << "line1" << e << endl;	
	}
else if (i1 == "s1" || i1 == "s2" || i1 == "s3"){
	s = i1;
	//cout << "line2" << s << endl;
	}
else if (i1 == "b1" || i1 == "b2" || i1 == "b3" || i1 == "b4" || i1 == "b5" || i1 == "b6" || i1 == "b7" || i1 == "b8"){
	b = i1;
	//cout << "line3" << b << endl;
	}
else {
	cout << "Invalid input, moving to next order" << endl;
	}




cout << "Next order" << endl;
cin >> i2;
if (i2 == "e1" || i2 == "e2" || i2 == "e3") {
	e = i2;
	//cout << "line1" << e << endl;	
	}
else if (i2 == "s1" || i2 == "s2" || i2 == "s3"){
	s = i2;
	//cout << "line2" << s << endl;
	}
else if (i2 == "b1" || i2 == "b2" || i2 == "b3" || i2 == "b4" || i2 == "b5" || i2 == "b6" || i2 == "b7" || i2 == "b8"){
	b = i2;
	//cout << "line3" << b << endl;
	}
else {
	cout << "Invalid input, moving to next order" << endl;
	}




cout << "Last order" << endl;
cin >> i3;
if (i3 == "e1" || i3 == "e2" || i3 == "e3") {
	e = i3;
	//cout << "line1" << e << endl;	
	}
else if (i3 == "s1" || i3 == "s2" || i3 == "s3"){
	s = i3;
	//cout << "line2" << s << endl;
	}
else if (i3 == "b1" || i3 == "b2" || i3 == "b3" || i3 == "b4" || i3 == "b5" || i3 == "b6" || i3 == "b7" || i3 == "b8"){
	b = i3;
	//cout << "line3" << b << endl;
	}
else {
	cout << "Invalid input, moving to bill generation" << endl;
	}




int a = 0;
int c = 0;
int d = 0;


//cout << "Your Lunch order is: " << e << endl;
//cout << "Your side order is: " << s << endl;
//cout << "Your beverages order is: " << b << endl;

if (e == "e1" || e == "e2" || e == "e3") {
    	cout << "Lunch order received" << endl;
	if (e =="e1"){
		a = 7;
		}
	else if (e== "e2"){
		a = 6;
		}
	else {
		a = 9;
		} 
  }
else	{
	cout << "Lunch: invalid input, moving to next order" << endl;
	}

if (s == "s1" || s == "s2" || s == "s3") {
    	cout << "Side order received" << endl;
	if (s =="s1"){
		c = 2;
		}
	else if (s== "s2"){
		c = 3;
		}
	else {
		c = 2;
		} 
 }
else	{
	cout << "Side: invalid input, moving to next order" << endl;
	}

if (b == "b1" || b == "b2" || b == "b3" || b == "b4" || b == "b5" || b == "b6" || b == "b7" || b == "b8") {
    	cout << "Beverages order received" << endl;
	if (b =="b1"){
		d = 0;
		}
	else if (b== "b2"){
		d = 2;
		}
	else if (b =="b3"){
		d = 4;
		}
	else if (b== "b4"){
		d = 6;
		}
	else if (b =="b5"){
		d = 7;
		}
	else if (b== "b6"){
		d = 7;
		}
	else if (b== "b7"){
		d = 1;
		}
	else {
		d =1;
		}


 }
else	{
	cout << "Side: invalid input, finishing the order" << endl;
	}

cout << "Lunch price is = " << a << endl;
cout << "Side price is = " << c << endl;
cout << "Beverages price is = " << d << endl;



if ( e == "e1" && s == "s1" && (b == "b1" || b=="b2" || b == "b7" || b == "b8" ) ){
	cout << "You got a special discount. Your bill is = $8 " << endl;
}

else if ( e == "e2" && s == "s2" && ( b == "b7" || b == "b8" ) ){
	cout << "You got a special discount. Your bill is = $7 " << endl;
}

else if ( e == "e3" && (s == "s1" || s == "s2" || s == "s3") && (b == "b3" || b=="b4" || b == "b5" || b == "b6" ) ){
	cout << "You got a special discount. Your bill is = $13 " << endl;
}

else {
	cout << "Your bill is = $" << (a+c+d) << endl;
}

cout << "Enjoy your meal!!" << endl;
return 0;
}
