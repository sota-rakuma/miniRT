### 第1回
```c
// 第1回
	// <P-C, P-C> = r^2 // 球
	// P = O + tD       // 視線上の任意の点

	// 計算過程
	// <O + tD -C, O + tD -C>   = r^2 
	// <O - C + tD, O - C + tD> = r^2
	// <CO + tD, CO + tD> = r^2

	// <CO, CO> + 2t<D, CO> + t^2 <D, D> - r^2 = 0 
	// a * t^2 + b * t + c = 0
	// t = <解の公式>  

	// t < 0: カメラより後ろ
	// 0 <= t <= 1: カメラとスクリーンの間
	// 1 < t: スクリーンの向こう側

	// 交差条件: tが実数(D >= b^2 - 4ac) && t > 1 

	// 交差条件を満たす物体が2つの場合
	// 	-> tが小さい方がスクリーンに映る
```
