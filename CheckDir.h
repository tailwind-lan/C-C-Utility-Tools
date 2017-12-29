#include <sys/stat.h>

const int PATH_NAME_MAX = 512;
using namespace std;

bool CreateDir(const char* pszPath)
{
    if (NULL == pszPath)
    {
        return false;
    }

    int nPathLen = strlen(pszPath);
    if (nPathLen >= PATH_NAME_MAX)
    {
        return false;
    }

    int nBeginCmpPath;
    int nEndCmpPath;
    char szCurrPath[PATH_NAME_MAX] = {0};
    char szFullPath[PATH_NAME_MAX] = {0};

    //relative path
    if (pszPath[0] != '/')
    {
        //to get current path
        getcwd(szCurrPath, sizeof(szCurrPath));
        strcat(szCurrPath, "/");
        nBeginCmpPath = strlen(szCurrPath);
        strcat(szCurrPath, pszPath);
        if(pszPath[nPathLen] != '/')
        {
            strcat(szCurrPath, "/");
        }

        nEndCmpPath = strlen(szCurrPath);
    }
    else
    {
        //absolute path
        int nPathLen = strlen(pszPath);
        strcpy(szCurrPath, pszPath);
        if(pszPath[nPathLen] != '/')
        {
            strcat(szCurrPath, "/");
        }

        nBeginCmpPath = 1;
        nEndCmpPath = strlen(szCurrPath);
    }

    //create path step-by-step
    for(int i = nBeginCmpPath; i < nEndCmpPath ; i++)
    {
        if('/' == szCurrPath[i])
        {
            szCurrPath[i] = '\0';
            if(access(szCurrPath, F_OK) != 0)
            {
                if(-1 == mkdir(szCurrPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
                {
                    cout << "mkdir <" << szCurrPath << "> failed." << endl;
                    return false;
                }
                else
                {
                    cout << "mkdir <" << szCurrPath << "> successful." << endl;
                }
            }

            szCurrPath[i] = '/';
        }
    }

    return true;
}
