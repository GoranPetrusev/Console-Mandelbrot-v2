#include <Windows.h>

const int n_screenWidth = 120;
const int n_screenHeight = 30;

int main()
{
	wchar_t* screen = new wchar_t[n_screenHeight * n_screenWidth];
	for( int i = 0; i < n_screenHeight * n_screenWidth; i++ ) screen[i] = L'#';
	HANDLE hConsole = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
	SetConsoleActiveScreenBuffer( hConsole );
	DWORD dwBytesWritten = 0;

	// Main Loop
	while( true )
	{

		// Displaying Frame
		WriteConsoleOutputCharacter( hConsole,screen,n_screenHeight * n_screenWidth,{ 0,0 },&dwBytesWritten );
	}
}