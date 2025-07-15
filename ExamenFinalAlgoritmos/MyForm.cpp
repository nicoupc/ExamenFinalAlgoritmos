#include "MyForm.h"

using namespace ExamenFinalAlgoritmos;

int main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main form
	MyForm^ form = gcnew MyForm();

	// Run the application
	Application::Run(form);

	return 0;
}