#include <os.h>
#include "PTTKiller.h"

int is_ptt(void)
{
        char buffer[PTT_BUF_SIZE] = {'\0'};
        NU_Current_Dir("A:", buffer);
        return strcmp(buffer, "\\documents\\");
}
 
int copy_file(const char *src, const char *dst)
{
        FILE *in = fopen(src, "rb"), *out;
        int c;
        if (!in)
                return -1;
        out = fopen(dst, "wb");
        if (!out) 
       {
                fclose(in);
                return -1;
        }
        while ((c = fgetc(in)) != EOF)
        {
                fputc(c, out);
        }
        fclose(in);
        fclose(out);
        return 0;
}

int PTTKiller(void)
{
        if (!is_ptt())
			return EXIT_FAILURE;

		struct dstat file;
        NU_Get_First(&file, PTT_SRC_DIR "*.*");
        do {
                char src[PTT_BUF_SIZE] = {'\0'};
                char dst[PTT_BUF_SIZE] = {'\0'};
                sprintf(src, PTT_SRC_DIR "%s", file.filepath);
                sprintf(dst, PTT_DST_DIR "%s", file.filepath);
                copy_file(src, dst);
        } while (NU_Get_Next(&file) == 0);
        NU_Done(&file);
		
        return EXIT_SUCCESS;
}
