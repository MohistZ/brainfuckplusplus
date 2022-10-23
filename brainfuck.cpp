#include <cstdio>
#include <fstream>
int main(int argc, char **argv)
{
    std::ifstream read;
    int r;
    char get;
    char arr[300010] = {0};
    char *main_ptr = arr + 15000;
    char *temp_ptr = main_ptr;
    char *ptr[10];
    int circulate_stack[200];
    int function_stack[200];
    int circulate_stack_top = 0, function_stack_top = 0;
    int debugger = 0;
    for (int i = 0; i < 10; i++) //
    {
        ptr[i] = arr + i + 30000;
    }
    for (int i = 1; i < argc; i++)
    {
        read.open(argv[i], std::ios::in);
        if (!read.is_open())
        {
            printf("\nNOT FOUND\n");
            return 0;
        }
        read >> std::noskipws;
        while (1)
        {
            read >> get;
            if (read.eof())
                break;
            switch (get)
            {
            case '>':
                read >> get;
                if (get == '@')
                {
                    read >> get;
                    main_ptr += *ptr[get - '0'];
                }
                else if (get >= '0' && get <= '9')
                {
                    if (get != '0')
                        main_ptr += get - '0';
                    else
                        main_ptr += 10;
                }
                else
                {
                    main_ptr++;
                    read.seekg(-1, std::ios::cur);
                }
                break;
            case '<':
                read >> get;
                if (get == '@')
                {
                    read >> get;
                    main_ptr -= *ptr[get - '0'];
                }
                else if (get >= '0' && get <= '9')
                {
                    if (get != '0')
                        main_ptr -= get - '0';
                    else
                        main_ptr -= 10;
                }
                else
                {
                    main_ptr--;
                    read.seekg(-1, std::ios::cur);
                }
                break;
            case '+':

                read >> get;
                if (get == '@')
                {
                    read >> get;
                    (*main_ptr) += *ptr[get - '0'];
                }
                else if (get >= '0' && get <= '9')
                {
                    if (get != '0')
                        *main_ptr += get - '0';
                    else
                        *main_ptr += 10;
                }
                else
                {
                    (*main_ptr)++;
                    read.seekg(-1, std::ios::cur);
                }
                break;
            case '-':
                read >> get;
                if (get == '@')
                {
                    read >> get;
                    (*main_ptr) -= *ptr[get - '0'];
                }
                else if (get >= '0' && get <= '9')
                {
                    if (get != '0')
                        *main_ptr -= get - '0';
                    else
                        *main_ptr -= 10;
                }
                else
                {
                    (*main_ptr)--;
                    read.seekg(-1, std::ios::cur);
                }
                break;
            case ':':
                printf("%d", int(*main_ptr));
                fflush(stdout);
                break;
            case '.':
                printf("%c", *main_ptr);
                fflush(stdout);
                break;
            case ',':
                *main_ptr = std::getchar();
                break;
            case '=':
                read >> get;
                *main_ptr = get;
                break;
            case '\"':
                while (1)
                {
                    read >> get;
                    if (get == '\"')
                        break;
                    *main_ptr = get;
                    main_ptr++;
                }
                break;
                // temp
            case '@':
                read >> get;
                *main_ptr = *ptr[get - '0'];
                break;
            case '&':
                read >> get;
                *ptr[get - '0'] = *main_ptr;
                break;
            case '*':
                read >> get;
                r = *ptr[get - '0'];
                *ptr[get - '0'] = *main_ptr;
                *main_ptr = r;
                break;
            case '^':
                read >> get;
                if (get >= '0' && get <= '9')
                {
                    ptr[get - '0'] = main_ptr;
                }
                else
                {
                    temp_ptr = main_ptr;
                    read.seekg(-1, std::ios::cur);
                }
                break;
            case 'v':
                read >> get;
                if (get >= '0' && get <= '9')
                {
                    main_ptr = ptr[get - '0'];
                }
                else
                {
                    main_ptr = temp_ptr;
                    read.seekg(-1, std::ios::cur);
                }
                break;
            case '!':
                main_ptr = arr + 15000;
                break;
            case '/':
                *main_ptr = 0;
                break;
            case '[':
                circulate_stack[circulate_stack_top++] = read.tellg();
                if (*main_ptr == 0)
                {
                    int z = 0;
                    while (read >> get)
                    {
                        if (get == '[')
                            z++;
                        if (get == ']')
                        {
                            z--;
                            if (z < 0)
                            {
                                z = 0;
                                break;
                            }
                        }
                    }
                    if (z != 0)
                    {
                        printf("\nERROR\n");
                        return 0;
                    }
                }
                break;
            case ']':
                if (*main_ptr != 0)
                {
                    read.seekg(circulate_stack[circulate_stack_top - 1]);
                }
                else
                {
                    circulate_stack_top--;
                }
                break;
            case '?':
                r = 0;
                read >> get;
                if (get == '@')
                {
                    read >> get;
                    r = *ptr[get - '0'];
                }
                else
                {
                    r = 0;
                    read.seekg(-1, std::ios::cur);
                }
                if (r != *main_ptr)
                {
                    read >> get;
                }
                break;
            case '(':
                r = 0;
                read >> get;
                if (get == '@')
                {
                    read >> get;
                    r = *ptr[get - '0'];
                }
                else
                {
                    r = 0;
                    read.seekg(-1, std::ios::cur);
                }
                if (r != *main_ptr)
                {
                    r = 0;
                    while (read >> get)
                    {
                        if (get == '(')
                            r++;
                        if (get == '\"')
                            while (read >> get)
                            {
                                if (get == '\"')
                                    break;
                            }
                        if (get == ')')
                        {
                            r--;
                            if (r < 0)
                                break;
                        }
                    }
                }
                break;
            case '$':
                read >> get;
                r = get;
                read.seekg(0);
                while (read >> get)
                {
                    if (get == '\"')
                        while (read >> get)
                        {
                            if (get == '\"')
                                break;
                        }
                    if (get == '#')
                    {
                        read >> get;
                        if (get == r)
                            break;
                    }
                }
                break;
            case '|':
                r = 0;
                read >> get;
                if (get == '@')
                {
                    read >> get;
                    r = *ptr[get - '0'];
                }
                else if (get >= '0' && get <= '9')
                {
                    r = get - '0';
                }
                else
                {
                    read.seekg(-1, std::ios::cur);
                }
                read.close();
                return r;
                break;
            case '%':
                while (read >> get)
                {
                    if (get == '\n')
                        break;
                }
                break;
            case '}':
                read.seekg(function_stack[function_stack_top - 1]);
                function_stack_top--;
                break;
            case '_':
                system("clear");
                break;
            case '\'':
                debugger++;
                printf("\n-----debugger%d----\n",debugger);
                printf("---pointer---\n");
                printf("main:    \tpoint at %d\tvalue: %d\tchar: %c\n", main_ptr - arr - 15000, *main_ptr, *main_ptr);
                if (temp_ptr == 0)
                    printf("temp:    \tpoint at %d\tvalue: %d\tchar: %c\n", temp_ptr - arr - 15000, *temp_ptr, *temp_ptr);
                for (int i = 0; i < 10; i++)
                {
                    if ((ptr[i] - arr) != 30000 + i || *ptr[i] != 0)
                        printf("pointer%d: \tpoint at %d\tvalue: %d\tchar: %c\n", i, ptr[i] - arr - 15000, *ptr[i], *ptr[i]);
                }
                printf("---array---\n");
                for (int i = 0; i < 30010; i++)
                {
                    if (arr[i] != 0)
                        printf("%d: %d %c\t", i - 15000, arr[i], arr[i]);
                }
                printf("\n------------------\n");
                break;
            default:
                if (get >= 'A' && get <= 'Z')
                {
                    r = get;
                    read >> get;
                    if (get != '{')
                    {
                        read.seekg(-1, std::ios::cur);
                        function_stack[function_stack_top++] = read.tellg();
                        read.seekg(0);
                        while (read >> get)
                        {
                            if (get == r)
                            {
                                read >> get;
                                if (get == '{')
                                    break;
                            }
                        }
                    }
                    else
                    {
                        while (read >> get)
                        {
                            if (get == '}')
                                break;
                        }
                    }
                }
                break;
            }
        }
        read.close();
    }
    return 0;
}