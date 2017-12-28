//获取当前路径
bool GetCwd(string &strCwd)
{
    char szCwd[512] = { 0 };

#ifdef WIN32
    GetModuleFileNameA(NULL, szCwd, 512);
    char* pTmp = szCwd + (strlen(szCwd) - 1);

    while ((pTmp != szCwd) && (*pTmp != '\\'))
    {
        *pTmp = '\0';
        pTmp--;
    }
#else
    //获取当前目录绝对路径
    if (NULL == getcwd(szCwd, 512))
        return false;

    szCwd[strlen(szCwd)] = '/';
#endif

    strCwd = szCwd;
    return !strCwd.empty();
}
