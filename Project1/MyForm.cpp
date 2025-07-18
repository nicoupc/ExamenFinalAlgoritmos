#include "MyForm.h"

using namespace Project1;

// Método para inicializar el formulario
int main(array<System::String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm());
	return 0;
}