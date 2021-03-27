#include "../inc/cub.h"

static void init_file_vble(t_cub *info)
{
    info->res.rend_x = 0;
	info->res.rend_y = 0;

	info->tex.path_norte = NULL;
	info->tex.path_sur = NULL;
	info->tex.path_oeste = NULL;
	info->tex.path_este = NULL;
	info->tex.path_sprite = NULL;

    ft_bzero(info->col.rgb_suelo, 3);
    ft_bzero(info->col.rgb_techo, 3);

	info->map = NULL;
}

static void init_mlx_vble(t_cub *info)
{
    info->libx.mlx = NULL;
	info->libx.window = NULL;
	info->libx.img = NULL;
}

static void init_mov_vble(t_cub *info)
{
    info->player.left = 0;
    info->player.right = 0;
    info->player.up = 0;
    info->player.down = 0;
    info->player.x = 0;
    info->player.y = 0;
    info->player.dir = (char)0;
    info->player.angle = 0.0;
    info->player.v = 0.0;
    info->player.turn = 0.0;

    info->cam.left = 0;
    info->cam.right = 0;
}

static void init_raycast_vble(t_cub *info)
{
    info->ray.alt_ant = 0.0;
    info->ray.ntecho_ant = 0.0;
    info->ray.nsuelo_ant = 0.0;
    info->ray.last_time = 0.0;
    info->ray.delta = 0.0;
}

void	init_struct(t_cub *info)
{
	init_file_vble(info);
    init_mlx_vble(info);
    init_mov_vble(info);
    init_raycast_vble(info);

    info->nrows = 0;
    info->resz_map = 0;
    info->resz_player = 0;
}