#include "error.h"
#include <iostream>

error::error( std::string errStr, std::string actStr )
{
	errorString = errStr;
	actionString = actStr;
	printError();  // print the error while constructing the error object
}
void error::printError()
{
  std::cerr << "Error:" << errorString << std::endl;
  std::cerr << "Action:" << actionString << std::endl;
}