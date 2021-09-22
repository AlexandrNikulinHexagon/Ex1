/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

class CmdBimTag
{
    public:
    class SavedSettings
    {
    public:
        int m_updateType = 1;
    };
    
    static inline SavedSettings s_settings;
};

int main()
{
    //CmdBimTag t;
    printf("Hello World %d", CmdBimTag::s_settings.m_updateType);

    return 0;
}
