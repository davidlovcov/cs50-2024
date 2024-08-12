#include <cs50.h>
#include <stdio.h>

int main()
{
    int height = 0;

    do
    {
        height = get_int("Let's build a pyramide. Give me a number between 1 and 8 inclusive! ");

        if (height > 0 && height < 9)
        {
            int currentRow = 1;

            while (currentRow <= height)
            {
                for (int i = 0; i < height - currentRow; i++) // prints spaces on left side
                {
                    printf(" ");
                }

                for (int j = 0; j < currentRow; j++) // prints left #
                {
                    printf("#");
                }

                printf("  "); // spaces between pyramid

                for (int k = 0; k < currentRow; k++) // prints right #
                {
                    printf("#");
                }

                printf("\n");

                currentRow++;
            }

            return 0;
        }
    }
    while (height < 1 || height > 8);
}
