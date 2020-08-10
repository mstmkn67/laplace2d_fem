
//Finite Element Method
// for 2 dimensional laplace equation  solver
//                                     Masato MAKINO 

#include "udf/gourmain.h"
#include "Laplace2dFEMSimulator.h"

void udfHeaderCheck()
{
	string version("1.0"),engine("laplace2d_fem");
	cout << "**************************************************************" << endl;
	cout <<  "      " <<  engine << "  " << version << "           " << endl;
	cout << "                                        Masato MAKINO         " << endl;
	cout << "**************************************************************" << endl;
	cout <<  endl;
}

void error_massage(){
	cout << "usage: laplace2d_fem -I input_udf [-O output_udf] " << endl;
}


int gourmain(UDFManager* in,UDFManager* out){
	udfHeaderCheck();
	Laplace2dFEMSimulator* sim=new Laplace2dFEMSimulator(in,out);
	sim->update();
	delete sim;
	return 0;
}
