#include "../inc/cub.h"

#define BMP_HEADER_BYTES    54
#define BYTE                256
#define DATA_INIT           54
#define BMP_HEADER_SIZE     40
#define NUM_PLANES          1
#define HORIZ_RESOLUTION    24

static int		write_bmp_header(t_cub *c, int fd, int filesize)
{
	int				i;
	unsigned char	bmpfileheader[BMP_HEADER_BYTES];
	(void)filesize;
	i = 0;
	while (i < BMP_HEADER_BYTES)
		bmpfileheader[i++] = (unsigned char)(0);

    ft_memcpy(bmpfileheader, "BM", 2);
    bmpfileheader[2] = filesize % BYTE;
    bmpfileheader[3] = (filesize >> 8) % BYTE;
    bmpfileheader[4] = (filesize >> 16) % BYTE;
    bmpfileheader[5] = (filesize >> 24) % BYTE;
	bmpfileheader[10] = (unsigned char)(DATA_INIT);
	bmpfileheader[14] = (unsigned char)(BMP_HEADER_SIZE);
    bmpfileheader[18] = c->res.rend_x % BYTE;
    bmpfileheader[19] = (c->res.rend_x >> 8) % BYTE;
    bmpfileheader[20] = (c->res.rend_x >> 16) % BYTE;
    bmpfileheader[21] = (c->res.rend_x >> 24) % BYTE;
	bmpfileheader[22] = c->res.rend_y % BYTE;
    bmpfileheader[23] = (c->res.rend_y >> 8) % BYTE;
    bmpfileheader[24] = (c->res.rend_y >> 16) % BYTE;
    bmpfileheader[25] = (c->res.rend_y >> 24) % BYTE;
	bmpfileheader[26] = (unsigned char)(NUM_PLANES);
	bmpfileheader[28] = (unsigned char)(HORIZ_RESOLUTION);
	return (!(write(fd, bmpfileheader, BMP_HEADER_BYTES) < 0));
}

static int		write_bmp_data(t_cub *c, int file, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					y;
	int					x;
	int					color;

	y = 0;
	while (y < c->res.rend_y)
	{
		x = 0;
		while (x < c->res.rend_x)
		{
			color = c->win.addr[c->res.rend_x * y + x];
			if (write(file, &color, 1) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int				save_bmp(t_cub *c)
{
	int			filesize;
	int			file = 0;
	int			pad;

	draw(c);
	pad = (4 - (c->res.rend_x * 3) % 4) % 4;
	filesize = BMP_HEADER_BYTES + (3 * (c->res.rend_x + pad) * c->res.rend_y);
	if ((file = open("prueba.bmp", O_CREAT | O_WRONLY, 0644)) < 0)
	{
		printf("fail open\n");
		return (0);
	}
	if (!write_bmp_header(c, file, filesize))
    {
        printf("fail bmp header\n");
		return (0);
    }
	if (!write_bmp_data(c, file, pad))
    {
        printf("fail bmp data\n");
		return (0);
    }
	close(file);
	exit_handler(c);
	return (1);
}
