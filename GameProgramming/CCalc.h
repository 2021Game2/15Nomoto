#pragma once
#include <math.h>

#define _OX_EPSILON_	0.000001f	// 誤差


bool isSharpAngle(const CVector& v1, const CVector& v2) {
	return (v1.Dot(v2) >= 0.0f);
}
//
//
//
//// 直線
//struct Line {
//	CVector p;
//	CVector v;		// 方向ベクトル
//	Line() : p(0.0f, 0.0f, 0.0f), v(1.0f, 0.0f, 0.0f) {}
//	Line(const CVector& p, const CVector& v) :p(p.mX, p.mY, p.mZ), v(v.mX, v.mY, v.mZ) {}
//	~Line() {}
//
//	// 点上の座標を取得
//	//  ベクトルに掛け算する係数
//	CVector getPoint(float t) const {
//		return p + v * t;
//	}
//};


// 線分
struct Segment {
	CVector p1;		//点１
	CVector p2;		//点２
	CVector v;		// 方向ベクトル

	Segment() {}
	Segment(const CVector& p1, const CVector& p2) :p1(p1), p2(p2), v(p2 - p1) {}

	// 終点を取得
	CVector getEndPoint() const {
		return p2;
	}
	// 点上の座標を取得
	//  ベクトルに掛け算する係数
	CVector getPoint(float t) const {
		return p1 + v * t;
	}
};




// カプセル
struct Capsule {
	Segment s;
	float r;	// 半径
	Capsule() : r(0.5f) {}
	Capsule(const CVector& v1, const CVector& v2, float r) :s(v1, v2), r(r) {}
	~Capsule() {}
};






// 点と直線の最短距離
// p : 点
// l : 直線
// h : 点から下ろした垂線の足（戻り値）
// t :ベクトル係数（戻り値）
// 戻り値: 最短距離
float calcPointLineDist(const CVector& p, const Segment& l, CVector& h, float& t) {

	float lenSqV = l.v.LengthSq();
	t = 0.0f;
	if (lenSqV > 0.0f) {
		t = l.v.Dot(p - l.p1) / lenSqV;
	}
	h = l.p1 + l.v * t;
	return (h - p).Length();
}

// ∠p1p2p3は鋭角？
bool isSharpAngle(const CVector& p1, const CVector& p2, const CVector& p3) {
	CVector tmp1(p1 - p2);
	CVector tmp2(p3 - p2);
	return isSharpAngle(tmp1, tmp2);
}
bool isParallel(CVector v1, CVector v2) {
	float d = v1.Cross(v2).LengthSq();
	return (-_OX_EPSILON_ < d&& d < _OX_EPSILON_);	// 誤差範囲内なら平行と判定
}

// 点と線分の最短距離
// p : 点
// seg : 線分
// h : 最短距離となる端点（戻り値）
// t : 端点位置（ t < 0: 始点の外, 0 <= t <= 1: 線分内, t > 1: 終点の外 ）
// 戻り値: 最短距離
float calcPointSegmentDist(const CVector& p, const Segment& seg, CVector& h, float& t) {

	const CVector e = seg.p2;

	// 垂線の長さ、垂線の足の座標及びtを算出
	float len = calcPointLineDist(p, Segment(seg.p1, e - seg.p1), h, t);

	if (isSharpAngle(p, seg.p1, e) == false) {
		// 始点側の外側
		h = seg.p1;
		return (seg.p1 - p).Length();
	}
	else if (isSharpAngle(p, e, seg.p1) == false) {
		// 終点側の外側
		h = e;
		return (e - p).Length();
	}

	return len;
}


// 2直線の最短距離
// l1 : L1
// l2 : L2
// p1 : L1側の垂線の足（戻り値）
// p2 : L2側の垂線の足（戻り値）
// t1 : L1側のベクトル係数（戻り値）
// t2 : L2側のベクトル係数（戻り値）
// 戻り値: 最短距離
float calcLineLineDist(const Segment& l1, const Segment& l2, CVector& p1, CVector& p2, float& t1, float& t2) {

	// 2直線が平行？
	if (isParallel(l1.v, l2.v) == true) {

		// 点P11と直線L2の最短距離の問題に帰着
		float len = calcPointLineDist(l1.p1, l2, p2, t2);
		p1 = l1.p1;
		t1 = 0.0f;

		return len;
	}

	// 2直線はねじれ関係
	float DV1V2 = l1.v.Dot(l2.v);
	float DV1V1 = l1.v.LengthSq();
	float DV2V2 = l2.v.LengthSq();
	CVector P21P11 = l1.p1 - l2.p1;
	t1 = (DV1V2 * l2.v.Dot(P21P11) - DV2V2 * l1.v.Dot(P21P11)) / (DV1V1 * DV2V2 - DV1V2 * DV1V2);
	p1 = l1.getPoint(t1);
	t2 = l2.v.Dot(p1 - l2.p1) / DV2V2;
	p2 = l2.getPoint(t2);

	return (p2 - p1).Length();
}

// 0～1の間にクランプ
void clamp01(float& v) {
	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

// 2線分の最短距離
// s1 : S1(線分1)
// s2 : S2(線分2)
// p1 : S1側の垂線の足（戻り値）
// p2 : S2側の垂線の足（戻り値）
// t1 : S1側のベクトル係数（戻り値）
// t2 : S2側のベクトル係数（戻り値）
// 戻り値: 最短距離
float calcSegmentSegmentDist(const Segment& s1, const Segment& s2, CVector& p1, CVector& p2, float& t1, float& t2, CVector& ret) {

	// S1が縮退している？
	if (s1.v.LengthSq() < _OX_EPSILON_) {
		// S2も縮退？
		if (s2.v.LengthSq() < _OX_EPSILON_) {
			// 点と点の距離の問題に帰着
			float len = (s2.p1 - s1.p1).Length();
			p1 = s1.p1;
			p2 = s2.p1;
			t1 = t2 = 0.0f;
			ret = (s2.p1 - s1.p1).Normalize();
			return len;
		}
		else {
			// S1の始点とS2の最短問題に帰着
			float len = calcPointSegmentDist(s1.p1, s2, p2, t2);
			p1 = s1.p1;
			t1 = 0.0f;
			clamp01(t2);
			return len;
		}
	}

	// S2が縮退している？
	else if (s2.v.LengthSq() < _OX_EPSILON_) {
		// S2の始点とS1の最短問題に帰着
		float len = calcPointSegmentDist(s2.p1, s1, p1, t1);
		p2 = s2.p1;
		clamp01(t1);
		t2 = 0.0f;
		return len;
	}

	/* 線分同士 */

	// 2線分が平行だったら垂線の端点の一つをP1に仮決定
	if (isParallel(s1.v, s2.v) == true) {
		t1 = 0.0f;
		p1 = s1.p1;
		float len = calcPointSegmentDist(s1.p1, s2, p2, t2);
		if (0.0f <= t2 && t2 <= 1.0f) {
			return len;
		}
	}
	else {
		// 線分はねじれの関係
		// 2直線間の最短距離を求めて仮のt1,t2を求める
		float len = calcLineLineDist(s1, s2, p1, p2, t1, t2);
		if (
			0.0f <= t1 && t1 <= 1.0f &&
			0.0f <= t2 && t2 <= 1.0f
			)
		{
			return len;
		}
	}

	// 垂線の足が外にある事が判明
	// S1側のt1を0～1の間にクランプして垂線を降ろす
	clamp01(t1);
	p1 = s1.getPoint(t1);
	float len = calcPointSegmentDist(p1, s2, p2, t2);
	if (0.0f <= t2 && t2 <= 1.0f) {
		return len;
	}

	// S2側が外だったのでS2側をクランプ、S1に垂線を降ろす
	clamp01(t2);
	p2 = s2.getPoint(t2);
	len = calcPointSegmentDist(p2, s1, p1, t1);
	if (0.0f <= t1 && t1 <= 1.0f) {
		return len;
	}
	// 双方の端点が最短と判明
	clamp01(t1);
	p1 = s1.getPoint(t1);
	return (p2 - p1).Length();
}


// カプセル同士の衝突判定
// c1 : S1(線分1)
// c2 : S2(線分2)
// 戻り値: 衝突していたらtrue
bool colCapsuleCapsule(const Capsule& c1, const Capsule& c2, CVector& adjust) {
	CVector p1, p2;
	float t1, t2;
	float d = calcSegmentSegmentDist(c1.s, c2.s, p1, p2, t1, t2, adjust);
	float len = ((c1.r + c2.r) - d);
	adjust = adjust * len;
	printf("d=%f\n", d);

	//	printf("p1=%f,%f,%f,p2=%f,%f,%f,t1=%f,t2=%f\n",p1.mX,p1.mY,p1.mZ,p2.mX,p2.mY,p2.mZ, t1, t2);
	//	printf("ad=%f,%f,%f\n",adjust.mX, adjust.mY, adjust.mZ);
	return (d <= c1.r + c2.r);
}
#pragma once
