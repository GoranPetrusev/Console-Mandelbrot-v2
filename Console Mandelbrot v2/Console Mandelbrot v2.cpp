#include <Windows.h>
#include <chrono>

const int n_screenWidth = 100;
const int n_screenHeight = 30;

const int max_iteration = 500;

int main()
{
	wchar_t* screen = new wchar_t[n_screenHeight * n_screenWidth];
	for( int i = 0; i < n_screenHeight * n_screenWidth; i++ ) screen[i] = L'#';
	HANDLE hConsole = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL );
	SetConsoleActiveScreenBuffer( hConsole );
	DWORD dwBytesWritten = 0;

	// Declaring the variables outside of the loops so they don't have to be created like a trillion times
	double x0,y0;
	double x,y;
	int iteration;
	double temp_x;
	int index;

	// Panning variables
	double scaling = 1.0;
	double x_off = 2.5;
	double y_off = 1;

	// Chrono bullshit
	std::chrono::steady_clock::time_point start;
	std::chrono::duration<double> runtime;
	double fElapsedTime = 0;

	// Main Loop
	while( true )
	{
		scaling *= (GetAsyncKeyState( 0x53 ))?1.03:1; // S - Scaling Down
		scaling /= (GetAsyncKeyState( 0x57 ))?1.03:1; // W - Scaling Up

		x_off += GetAsyncKeyState( VK_LEFT )?3 * fElapsedTime:0;
		x_off -= GetAsyncKeyState( VK_RIGHT )?3 * fElapsedTime:0;
		y_off += GetAsyncKeyState( VK_UP )?3 * fElapsedTime:0;
		y_off -= GetAsyncKeyState( VK_DOWN )?3 * fElapsedTime:0;


		start = std::chrono::steady_clock::now();


		for( int py = 0; py < n_screenHeight; py++ )
		{
			y0 = ((double)py * 0.066666666667 - y_off) * scaling;

			for( int px = 0; px < n_screenWidth; px++ )
			{
				x0 = ((double)px * 0.035 - x_off) * scaling;

				x = 0.0;
				y = 0.0;
				iteration = 0;

				while( x * x + y * y <= 4 && iteration < max_iteration )
				{
					temp_x = x * x - y * y + x0;
					y = 2 * x * y + y0;
					x = temp_x;

					iteration++;
				}

				screen[py * n_screenWidth + px] = L" .,~-=+'^\"![*oqaOQH@G#"[int( iteration * 0.042 )];
			}
		}

		runtime = std::chrono::steady_clock::now() - start;
		fElapsedTime = runtime.count();

		// Displaying Frame
		WriteConsoleOutputCharacter( hConsole,screen,n_screenHeight * n_screenWidth,{ 0,0 },&dwBytesWritten );
	}
}