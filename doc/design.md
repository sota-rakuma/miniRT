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
	// 
	// if (shape == NULL)
	//   imageに背景色をput
	//   return
	// 
	// intensity = t_color{0, 0, 0}
	// for (lightのリストを回す)
	//   if (環境光)
	//     intensity += radience_amb（環境光）
	//   if (ライト=点光源)
	//     intensity += radience_dif（拡散反射光を計算）
	//     intensity += radience_spe（鏡面反射光を計算）
	// normalizeしたintensityをimageにput
```
