# design
```c
// world構造体
// {
// lightの線形リスト（環境光、ライト）
// shapeの線形リスト（球、平面、円柱）
// カメラ（位置、向き）
// }

main()
	// 引数チェック

	// 引数のファイルをパース ＝ world構造体を作成
	//   A、Lならlightリストにpush
	//   sp,pl,cyなら shapeリストにpush （反射係数を計算）
	//   Cなら cameraにセット

	// スクリーンの座標を計算 （カメラの位置、向きを使う）

	// for(スクリーンのy軸)
	//   for(スクリーンのx軸)
	//     [ピクセル単位の処理]関数

	// [ピクセル単位の処理]関数
	// *shape = get(視線先と交差するshape) <- shapeのリストを回して、t>=1かつmin(t)を取得

	// if (shape == NULL)
	//   imageに背景色をput
	//   return

	// intensity = t_color{0, 0, 0}
	// for (lightのリストを回す)
	//   if (環境光)
	//     intensity += radience_amb（環境光）
	//   if (ライト=点光源)
	//     intensity += radience_dif（拡散反射光を計算）
	//     intensity += radience_spe（鏡面反射光を計算）
	// normalizeしたintensityをimageにput
```




```c
/*
	lightの線形リスト (pos, intensity, type)
	shapeの線形リスト (sp, cy, pl....)
		void *で各図形をもつ. 共通部分(t, type, ...)はshapeが持つ
	c_to_s(カメラとスクリーンのベクトルを持つ構造体)

	for(y):
	for(x):
		shape min;

		shape *[交差判定]の関数(c_to_s, t_shape, double (*f())[])
		{↑関数ポインタ使えそう? 各図形でif文を使用する必要があるかも。あまりしたくないけど、思いついてない。無駄に計算しているところがあるかもしれない。}
			for (shape)
				shape = NULL;
				f[t_shape.type](t_shape ↑param); ← t_shapeのtに値を代入
				if (shape == NULL)
					shape = param;
				else if (shape && param.t >= 1.0)
					min(param, t_shape.t);
			return (shape);

		if (shape)
			lightの計算で必要なもの
			・[ 環境光 | 拡散反射 | 鏡面反射 ] 係数 in t_shape → k とする
				t_rad{
					t_color amb,
					t_color dif,
					t_color spe}
			・環境光と直接光の強度					in t_light
			・交差位置								camera + td
			・光沢度								in t_shape
			[intensityの計算をする]関数(t_light, 交差位置, shape)
				t_rad rad = (t_rad){
					(t_color){},
					(t_color){},
					(t_color){}
				}
				t_color intensity;

				for (t_light)
					if (t_light.type == 環境光)
						rad.amb += t_light.intensity;
					else
						t_vec3d normal = [法線ベクトルをもとめる]関数(shape, 交差位置);
						t_vec3d light_dir = t_light.pos - 交差位置;
						t_vec3d v = 交差位置の逆単位ベクトル
						t_vec3d r = 2 * <normal, light_dir> * normal - light_dir;

						rad.dif += [拡散反射光or鏡面反射光 を求める]関数
								(t_light.intensity, <normal, light_dir>, 1);
						rad.spe +=  [拡散反射光or鏡面反射光 を求める]関数
								(t_light.intensity, <r, light_dir>, shape.shininess);
				intensity =
				shape.k.amb * rad.amb
				+ shape.k.dif * rad.dif
				+ shape.k.spe * rad.spe;
				return (intensity);
*/
```

```c
// それぞれのshapeについて、交差判定を行い、視線ベクトルの方向ベクトルの係数tの値で判定する
// tは常に小さい値のみ保存しておくだけで、よさそう。

// また、どんな順番でもできるように shape の情報も保持しておく必要がありそう
```

```c
// 環境光		: ka * { Ia_1 + Ia_2 }

// 拡散反射光	: kd * { (Ii_1 * <n, l_1>) + (Ii_2 * <n, l_2>) }
// n   -> 法線ベクトルを求める(外積) <- 平面の場合、単純に外
//↑ 一般化
// 曲面を持つかどうかの判定 ← どうする？
// いや、各変数について偏微分すればいい？
// 今回に限っては2乗の式しかでないなら、式はほぼ固定
// ただ、そうなると各図形に法線ベクトルを求める式が必要になる

// l_x -> 光源x - 視線ベクトル

// [拡散反射光を求める]関数
	// (光源のintensity, 法線ベクトルn, 入射ベクトルl, {拡散反射係数kd})

// 鏡面反射光	: ks * { (Ii_1 * <v, r_1>^α) + (Ii_2 * <v, r_2>^α) }
// v   -> 視線ベクトルの逆単位ベクトル
// r_x -> 正反射ベクトル(2 * (cosθ * n) - l) -> 2 * <n, l> * n - l;

// [鏡面反射光を求める]関数
// 渡す実引数が 強度 と <v, r>^α であれば、 [拡散反射光を求める]関数と同じ
// ↑α を powの第二引数に渡すか、 whileで回すようにすれば一つでいけそう

// [拡散反射光or鏡面反射光 を求める]関数(直接光の強度, 内積の結果, べき数)

// 個人的には係数は各光源ごとにかけるのではなくて、最後にかけて足したい。
// 効果は如何程かわからないが、少しは早くなる気がする。
```