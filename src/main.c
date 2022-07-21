#include "minirt.h"

int key_event(int key_code, void *param) {
    printf("key_code: %d\n", key_code);
    if (key_code == 65307)
        exit(0);
    return (0);
}

t_vec3d get_vec_camera_to_screen(t_world *world, t_vec3d screen_p) {
    return (vec3d_sub(screen_p, world->camera->pos));
}

t_vec3d vec3d_camera(t_camera *camera) {
    return (camera->pos);
}

t_vec3d vec3d_sp_center(t_shape *shape) {
    return (shape->center);
}

int main(void) {
    void *mlx = mlx_init();
    if (mlx == NULL) {
        printf("initialized mlx error\n");
        exit(0);
    }
    // void *win = win_init(mlx, "hello world");

    t_screen *screen = screen_init("miniRT");

    int height = HEIGHT;
    int width = WIDTH;

    // ファイルをパース
    t_world *world = world_init();

    // 視点の位置を決める
    t_camera *camera = world->camera;

    // 球
    t_shape sp = *(world->shape_list);

    // 点光源
    t_light light = *(world->light_list);

    // 背景
    t_color bg = world->bg;

    // スクリーン上の点
    t_vec3d screen_p;
    screen_p.z = 0;
    double min_p = -1.0;
    double max_p = 1.0;

    // forで回す
    long y;
    long x;
    y = 0;
    while (y < height) {
        screen_p.y = max_p - ((max_p - min_p) / (double)height * (double)y);
        x = 0;
        while (x < width) {
            screen_p.x = (max_p - min_p) / (double)width * (double)x + min_p;

            // カメラから一番近いshapeを取得する--------------------------
            // 視線ベクトル
            // t_vec3d d = vec3d_sub(screen_p, camera.pos);
            // t_vec3d d = vec3d_sub(screen_p, world->camera.pos);
            t_vec3d o_to_screen = get_vec_camera_to_screen(world, screen_p);
            t_shape *now_shape = world->shape_list;
            double minimum_t = -1;
            t_shape *nearest_shape = NULL;
            while (now_shape) {
                // 球の中心 - カメラ ベクトル
                t_vec3d center_to_o = vec3d_sub(vec3d_camera(world->camera),
                                                vec3d_sp_center(&sp));
                // 判別式
                double a = vec3d_dot(o_to_screen, o_to_screen);
                double b = 2 * vec3d_dot(o_to_screen, center_to_o);
                double c =
                    vec3d_dot(center_to_o, center_to_o) - sp.radius * sp.radius;
                double discriminant = b * b - 4 * a * c;

                double t = -1;
                if (discriminant == 0)
                    t = -b / (2 * a);
                else if (discriminant > 0) {
                    double t1 = (-b - sqrt(discriminant)) / (2 * a);
                    double t2 = (-b + sqrt(discriminant)) / (2 * a);
                    double t_min = t1 > t2 ? t2 : t1;
                    double t_max = t1 > t2 ? t1 : t2;
                    t = t1 > 0 && t2 > 0 ? t_min : t_max;
                }
                if (t >= 1 && (nearest_shape == NULL || minimum_t > t)) {
                    nearest_shape = now_shape;
                    minimum_t = t;
                }

                now_shape = now_shape->next;
            }

            // パラメータ
            //t_color ii = (t_color){1.0, 1.0, 1.0}; // 光源の光の強度
            double alpha = 8.0;                    // 光沢度

            // 光の強度
            t_color intensity = (t_color){0.0, 0.0, 0.0};

            if (minimum_t > 0) {
                t_light *now_light = world->light_list;
                while (now_light) {
                    // 環境光
                    if (now_light->kind == AMBIENT_LIGHT) {
                        t_color ia = color_mult_num(now_light->color,
                                                    now_light->intensity / 255.0);
                        t_color radience_amb =
                            color_mult_color(ia, nearest_shape->ka);
                        intensity = color_add_color(intensity, radience_amb);
                    }
                    // 点光源
                    if (now_light->kind == LIGHT) {
                        // 交差位置: 球面上の点 P = O + tD
                        t_vec3d int_pos = vec3d_add(
                            camera->pos, vec3d_mult(o_to_screen, minimum_t));
                        // 入射ベクトル: 点光源 - 交差位置
                        //  -> 単位ベクトル
                        t_vec3d light_dir = vec3d_sub(now_light->pos, int_pos);
                        light_dir = vec3d_mult(light_dir,
                                               1.0 / vec3d_length(light_dir));
                        // 法線ベクトル: 交差位置(球面上の点) - 球中心
                        //  -> 単位ベクトル
                        t_vec3d normal = vec3d_sub(int_pos, sp.center);
                        normal = vec3d_mult(normal, 1.0 / vec3d_length(normal));

						t_color ii = color_mult_num(now_light->color, now_light->intensity / 255.0);

                        // 拡散反射光 ----------------------------------------
                        // vec3d_dot(入射ベクトル, 法線ベクトル) =
                        // |入射ベクトル||法線ベクトル|cosA
                        //  = 1 * 1 * cosA = cosA
                        double cosA = vec3d_dot(light_dir, normal);
                        cosA = cosA >= 0 ? cosA : 0.0;
                        t_color radience_dif = color_mult_num(
                            color_mult_color(nearest_shape->kd, ii), cosA);
                        // intensity = color_add_color(intensity, radience_dif);

                        // 鏡面反射光 ----------------------------------------
                        t_color radience_spe = (t_color){0.0, 0.0, 0.0};
                        if (cosA > 0) {
                            //正反射ベクトル
                            t_vec3d r = vec3d_sub(
                                vec3d_mult(normal, 2 * (cosA)), light_dir);
                            // 視線ベクトルの逆単位ベクトル
                            t_vec3d v = vec3d_mult(
                                int_pos, -1.0 * 1.0 / vec3d_length(int_pos));
                            // 視線ベクトルの逆単位ベクトルと正反射ベクトルの内積
                            double v_dot_r = vec3d_dot(v, r);
                            v_dot_r = v_dot_r >= 0 ? v_dot_r : 0.0;
                            radience_spe = color_mult_num(
                                color_mult_color(nearest_shape->ks, ii),
                                pow(v_dot_r, alpha));
                        }
                        // intensity = color_add_color(intensity, radience_spe);
                    }
                    now_light = now_light->next;
                }
            }

            // [0, 1]に収める
            intensity = color_normalize(intensity);

            t_color screen_color;
            if (minimum_t > 0) {
                screen_color = color_mult_num(intensity, 255.0);
            } else {
                screen_color = bg;
            }
            img_pixel_put(screen->_img, x, y, convert_color(screen_color));
            x++;
        }
        y++;
    }

    mlx_put_image_to_window(screen->_mlx, screen->_win, screen->_img->_img, 0,
                            0);

    mlx_key_hook(screen->_win, key_event, NULL);
    mlx_loop(screen->_mlx);
    return (0);
}
