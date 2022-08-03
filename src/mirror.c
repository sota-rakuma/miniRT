#include "minirt.h"

t_color compute_mirror(t_world *world, t_shape *shape, t_vec3d o_to_screen, double t, long count, t_vec3d pos)
{
    if (count > 3)
        return (t_color){0, 0, 0};

    // 正反射ベクトルを計算
    t_vec3d l =vec3d_mult(o_to_screen, -1);
    l = vec3d_unit(l);
    t_vec3d r = vec3d_mult(shape->oriental_normal, 2 * vec3d_dot(shape->oriental_normal, l));
    r = vec3d_sub(r, l);

    // double (*shape_get_intersection[])() = {with_sphere, with_plane, with_cylinder};

    t_camera *camera;
    camera = malloc(sizeof(t_camera));
    camera->pos = pos;
    o_to_screen = r;

    t_shape *now_shape = world->shape_list;
    double minimum_t = -1.0;
    t_shape *nearest_shape = NULL;
    while (now_shape)
    {
        if (now_shape == shape) {
            now_shape = now_shape->next;
            continue;
        }
        double t = -1.0;
        t = shape_get_intersection(
            o_to_screen, camera->pos, now_shape);
        if (t > 0.0 && (nearest_shape == NULL || minimum_t > t))
        {
            nearest_shape = now_shape;
            minimum_t = t;
        }
        now_shape = now_shape->next;
    }

    // // 鏡か？
    // if (nearest_shape && nearest_shape->is_mirror)
    // {
    //     t_vec3d pos =vec3d_add(pos, vec3d_mult(o_to_screen, minimum_t));
    //     t_color color = compute_mirror(world, nearest_shape, o_to_screen, minimum_t, count+1, pos);
    //     return color;
    // }

    // パラメータ
    // t_color ii = (t_color){1.0, 1.0, 1.0}; // 光源の光の強度
    // 光の強度
    t_color intensity = (t_color){0.0, 0.0, 0.0};

    if (minimum_t > 0)
    {
        t_light *now_light = world->light_list;

        while (now_light)
        {
            // 環境光
            if (now_light->kind == AMBIENT_LIGHT)
            {
                t_color ia = color_mult_num(
                    now_light->color, now_light->intensity / 255.0);
                t_color radience_amb =
                    color_mult_color(ia, nearest_shape->ka);
                intensity = color_add_color(intensity, radience_amb);
            }
            // 点光源
            if (now_light->kind == LIGHT)
            {
                // 交差位置: 球面上の点 P = O + tD
                t_vec3d int_pos = vec3d_add(
                    camera->pos, vec3d_mult(o_to_screen, minimum_t));

                // 付影処理
                bool flag = false;
                t_shape *loop_shape = world->shape_list;
                t_vec3d int_to_light_dir = vec3d_sub(now_light->pos, int_pos);
                while (loop_shape)
                {
                    double t = shape_get_intersection(
                        int_to_light_dir,
                        vec3d_add(int_pos, vec3d_mult(vec3d_unit(int_to_light_dir), 0.000000001)),
                        loop_shape);
                    if (0.0 < t && t < 1.0)
                    {
                        flag = true;
                        break;
                    }
                    loop_shape = loop_shape->next;
                }
                if (flag)
                {
                    now_light = now_light->next;
                    continue;
                }

                // 入射ベクトル: 点光源 - 交差位置
                //  -> 単位ベクトル
                t_vec3d light_dir = vec3d_sub(now_light->pos, int_pos);
                light_dir = vec3d_mult(light_dir,
                                       1.0 / vec3d_length(light_dir));

                t_vec3d normal;
                // 法線ベクトル[球]     : 交差位置(球面上の点) - 球中心
                // 法線ベクトル[平面]   : t_shapeの要素
                //  -> 単位ベクトル
                if (nearest_shape->kind == SPHERE)
                    normal = vec3d_sub(int_pos, nearest_shape->center);
                else if (nearest_shape->kind == PLANE)
                    normal = nearest_shape->oriental_normal;
                else if (nearest_shape->kind == CYLINDER)
                {
                    normal = vec3d_cross(vec3d_sub(int_pos, nearest_shape->center), nearest_shape->oriental_normal);
                    normal = vec3d_cross(nearest_shape->oriental_normal, normal);
                }
                // 視線ベクトルの逆単位ベクトルと法線ベクトルのなす角が90度以上なら逆に向ける
                // 視線ベクトルの逆単位ベクトル
                t_vec3d v = vec3d_unit(vec3d_mult(o_to_screen, -1.0));
                if (vec3d_dot(v, normal) <= 0.0)
                    normal = vec3d_mult(normal, -1.0);
                normal = vec3d_unit(normal);

                t_color ii = color_mult_num(
                    now_light->color, now_light->intensity / 255.0);

                // 拡散反射光 ----------------------------------------
                // vec3d_dot(入射ベクトル, 法線ベクトル) =
                // |入射ベクトル||法線ベクトル|cosA
                //  = 1 * 1 * cosA = cosA
                double cosA = vec3d_dot(light_dir, normal);
                cosA = cosA >= 0 ? cosA : 0.0;
                t_color radience_dif = color_mult_num(
                    color_mult_color(nearest_shape->kd, ii), cosA);
                intensity = color_add_color(intensity, radience_dif);

                // 鏡面反射光 ----------------------------------------
                t_color radience_spe = (t_color){0.0, 0.0, 0.0};
                if (cosA > 0)
                {
                    //正反射ベクトル
                    t_vec3d r = vec3d_sub(
                        vec3d_mult(normal, 2 * (cosA)), light_dir);
                    // 視線ベクトルの逆単位ベクトル
                    // t_vec3d v = vec3d_mult(
                    //    o_to_screen, -1.0 * 1.0 / vec3d_length(o_to_screen));
                    // 視線ベクトルの逆単位ベクトルと正反射ベクトルの内積
                    double v_dot_r = vec3d_dot(v, r);
                    v_dot_r = v_dot_r >= 0 ? v_dot_r : 0.0;
                    radience_spe = color_mult_num(
                        color_mult_color(nearest_shape->ks, ii),
                        pow(v_dot_r, nearest_shape->shininess));
                }
                intensity = color_add_color(intensity, radience_spe);
            }
            now_light = now_light->next;
        }
    }

    // [0, 1]に収める
    intensity = color_normalize(intensity);

    t_color screen_color;
    if (minimum_t > 0)
    {
        screen_color = color_mult_num(intensity, 255.0);
    }
    else
    {
        screen_color = world->bg;
    }

    return screen_color;
}