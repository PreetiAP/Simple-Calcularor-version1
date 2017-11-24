////////////////////////////////////////////////////////////

//Application: Calculator
//Author: Preeti

////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

using namespace std;

struct UserData
{
   int mathOperation;//TBD: Dictionary/tuple/list to store mathOperation names? and then print counter+each(list item )
   double number1, number2;
};

template<typename TYPE>
TYPE ReadValue(TYPE t, string msg)
{
   bool toRepeatInput;
   TYPE input;
   do 
   {
      toRepeatInput = false;
      cout<<msg;
      cin>>input;

      if (cin.good())
         // valid number
         break;
      else {
         // not a valid number
         cout << "\nInvalid Input! Please input a numerical value." << endl;
         cin.clear();
         cin.ignore(100000, '\n');
         toRepeatInput = true;
      }
   } while (toRepeatInput);
   return input;

}

UserData GetUserInput()
{
   UserData data;
   int temp=0;
   
   
   cout<<"\n======== SIMPLE CALCULATOR OPTIONS ========\n";
   cout<<"1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Modulus\n=========================";
   //cin>>data.mathOperation;
   data.mathOperation = ReadValue(temp, "\nPlease enter your option: ");


   if (data.mathOperation<6 && data.mathOperation>0)
   {
      data.number1 = ReadValue((double)temp, "\nEnter 1st number: ");
      data.number2 = ReadValue((double)temp, "\nEnter 2nd number: ");
   }
   return data;

   //Here cin.good() or cin.fail() can be used to validate user input as a double.
   //failbit will be set after using an extraction operator if there was a parse error, there are a couple simple test functions good and fail you can check. 
   //They are exactly the opposite of each other because they handle eofbit differently, but that's not an issue in this example.
   //Then, you have to clear failbit before trying again.
   //For valid input(double), cin.good() returns 1 (0 for invalid) and cin.fail() returns 0 (1 for invalid)
}

class ZeroDivisionException :public exception
{
public:
   ZeroDivisionException(double data)
   {
      someData = data;
   }
   //override what function
   const char* what()
   {
      return "Zero division error\n";
   }
   int someData;
};

class MyCalculator
{
   private:
      double num1,num2;
      int operation;
   public:
      MyCalculator(double n1, double n2, int op)
      {
         num1 = n1;
         num2 = n2;
         operation = op;

      }
      void Add(double n1, double n2)
      {
         cout<<n1<<"+"<<n2<<"="<<n1+n2<<endl;
      }
      void Subtract(double n1, double n2)
      {
         cout<<n1<<"-"<<n2<<"="<<n1-n2<<endl;
      }
      void Multiply(double n1, double n2)
      {
         cout<<n1<<"*"<<n2<<"="<<n1*n2<<endl;
      }
      void Divide(double n1, double n2)
      {
         if( (int)n2==0)
         {
            cout<<"Cannot divide by zero";
            //throw ZeroDivisionException(n1); //Commenting it to avoid closing application abruptly after exception
         }
         else
            cout<<n1<<"/"<<n2<<"="<<n1/n2<<endl;
      }
      void Modulo(double n1, double n2)
      {
         cout<<n1<<"%"<<n2<<"="<<(int)n1%(int)n2<<endl;
      }
      friend void PerformOperation(MyCalculator);
};

void PerformOperation(MyCalculator calObj)
{
   switch(calObj.operation)
   {
   case 1:
      {
         cout<<"Addition.....\n";
         calObj.Add(calObj.num1, calObj.num2);
         break;
      } 
   case 2:
      {
         cout<<"Subtraction.....\n";
         calObj.Subtract(calObj.num1, calObj.num2);
         break;
      }
   case 3:
      {
         cout<<"Multiplication.....\n";
         calObj.Multiply(calObj.num1, calObj.num2);
         break;
      }
   case 4:
      {
         cout<<"Division.....\n";
         calObj.Divide(calObj.num1, calObj.num2);
         break;
      }
   case 5:
      {
         cout<<"Modulus.....\n";
         calObj.Modulo(calObj.num1, calObj.num2);
         break;
      }
   default:
      cout<<"Invalid selection\n";
   }
}

int main()
{
   char toContinue;
   try
   {
      do 
      {
         UserData data = GetUserInput();

         MyCalculator calObj(data.number1, data.number2, data.mathOperation);

         PerformOperation(calObj);
         cout<<"\n\n\nDo you want to continue ?\nPress y/Y to continue ...";
         cin>>toContinue;

      } while (toContinue=='y' || toContinue=='Y');

      cout<<"\n\nThanks for using this application ...";
      getchar();
   }
   catch (ZeroDivisionException e) //catch DivideByZero exceptions
   {
      cout << e.what() << endl;
      cout << "Trying to divide " << e.someData << " by zero" << endl;
   }
   catch (exception e) //catch all exceptions
   {
      cout<<"\nException occured:\n\t"<<e.what()<<endl;
   }
   
   return 0;
}


