#pragma once
#include <math.h>

#define _OX_EPSILON_	0.000001f	// �덷


bool isSharpAngle(const CVector& v1, const CVector& v2) {
	return (v1.Dot(v2) >= 0.0f);
}
//
//
//
//// ����
//struct Line {
//	CVector p;
//	CVector v;		// �����x�N�g��
//	Line() : p(0.0f, 0.0f, 0.0f), v(1.0f, 0.0f, 0.0f) {}
//	Line(const CVector& p, const CVector& v) :p(p.mX, p.mY, p.mZ), v(v.mX, v.mY, v.mZ) {}
//	~Line() {}
//
//	// �_��̍��W���擾
//	//  �x�N�g���Ɋ|���Z����W��
//	CVector getPoint(float t) const {
//		return p + v * t;
//	}
//};


// ����
struct Segment {
	CVector p1;		//�_�P
	CVector p2;		//�_�Q
	CVector v;		// �����x�N�g��

	Segment() {}
	Segment(const CVector& p1, const CVector& p2) :p1(p1), p2(p2), v(p2 - p1) {}

	// �I�_���擾
	CVector getEndPoint() const {
		return p2;
	}
	// �_��̍��W���擾
	//  �x�N�g���Ɋ|���Z����W��
	CVector getPoint(float t) const {
		return p1 + v * t;
	}
};




// �J�v�Z��
struct Capsule {
	Segment s;
	float r;	// ���a
	Capsule() : r(0.5f) {}
	Capsule(const CVector& v1, const CVector& v2, float r) :s(v1, v2), r(r) {}
	~Capsule() {}
};






// �_�ƒ����̍ŒZ����
// p : �_
// l : ����
// h : �_���牺�낵�������̑��i�߂�l�j
// t :�x�N�g���W���i�߂�l�j
// �߂�l: �ŒZ����
float calcPointLineDist(const CVector& p, const Segment& l, CVector& h, float& t) {

	float lenSqV = l.v.LengthSq();
	t = 0.0f;
	if (lenSqV > 0.0f) {
		t = l.v.Dot(p - l.p1) / lenSqV;
	}
	h = l.p1 + l.v * t;
	return (h - p).Length();
}

// ��p1p2p3�͉s�p�H
bool isSharpAngle(const CVector& p1, const CVector& p2, const CVector& p3) {
	CVector tmp1(p1 - p2);
	CVector tmp2(p3 - p2);
	return isSharpAngle(tmp1, tmp2);
}
bool isParallel(CVector v1, CVector v2) {
	float d = v1.Cross(v2).LengthSq();
	return (-_OX_EPSILON_ < d&& d < _OX_EPSILON_);	// �덷�͈͓��Ȃ畽�s�Ɣ���
}

// �_�Ɛ����̍ŒZ����
// p : �_
// seg : ����
// h : �ŒZ�����ƂȂ�[�_�i�߂�l�j
// t : �[�_�ʒu�i t < 0: �n�_�̊O, 0 <= t <= 1: ������, t > 1: �I�_�̊O �j
// �߂�l: �ŒZ����
float calcPointSegmentDist(const CVector& p, const Segment& seg, CVector& h, float& t) {

	const CVector e = seg.p2;

	// �����̒����A�����̑��̍��W�y��t���Z�o
	float len = calcPointLineDist(p, Segment(seg.p1, e - seg.p1), h, t);

	if (isSharpAngle(p, seg.p1, e) == false) {
		// �n�_���̊O��
		h = seg.p1;
		return (seg.p1 - p).Length();
	}
	else if (isSharpAngle(p, e, seg.p1) == false) {
		// �I�_���̊O��
		h = e;
		return (e - p).Length();
	}

	return len;
}


// 2�����̍ŒZ����
// l1 : L1
// l2 : L2
// p1 : L1���̐����̑��i�߂�l�j
// p2 : L2���̐����̑��i�߂�l�j
// t1 : L1���̃x�N�g���W���i�߂�l�j
// t2 : L2���̃x�N�g���W���i�߂�l�j
// �߂�l: �ŒZ����
float calcLineLineDist(const Segment& l1, const Segment& l2, CVector& p1, CVector& p2, float& t1, float& t2) {

	// 2���������s�H
	if (isParallel(l1.v, l2.v) == true) {

		// �_P11�ƒ���L2�̍ŒZ�����̖��ɋA��
		float len = calcPointLineDist(l1.p1, l2, p2, t2);
		p1 = l1.p1;
		t1 = 0.0f;

		return len;
	}

	// 2�����͂˂���֌W
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

// 0�`1�̊ԂɃN�����v
void clamp01(float& v) {
	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;
}

// 2�����̍ŒZ����
// s1 : S1(����1)
// s2 : S2(����2)
// p1 : S1���̐����̑��i�߂�l�j
// p2 : S2���̐����̑��i�߂�l�j
// t1 : S1���̃x�N�g���W���i�߂�l�j
// t2 : S2���̃x�N�g���W���i�߂�l�j
// �߂�l: �ŒZ����
float calcSegmentSegmentDist(const Segment& s1, const Segment& s2, CVector& p1, CVector& p2, float& t1, float& t2, CVector& ret) {

	// S1���k�ނ��Ă���H
	if (s1.v.LengthSq() < _OX_EPSILON_) {
		// S2���k�ށH
		if (s2.v.LengthSq() < _OX_EPSILON_) {
			// �_�Ɠ_�̋����̖��ɋA��
			float len = (s2.p1 - s1.p1).Length();
			p1 = s1.p1;
			p2 = s2.p1;
			t1 = t2 = 0.0f;
			ret = (s2.p1 - s1.p1).Normalize();
			return len;
		}
		else {
			// S1�̎n�_��S2�̍ŒZ���ɋA��
			float len = calcPointSegmentDist(s1.p1, s2, p2, t2);
			p1 = s1.p1;
			t1 = 0.0f;
			clamp01(t2);
			return len;
		}
	}

	// S2���k�ނ��Ă���H
	else if (s2.v.LengthSq() < _OX_EPSILON_) {
		// S2�̎n�_��S1�̍ŒZ���ɋA��
		float len = calcPointSegmentDist(s2.p1, s1, p1, t1);
		p2 = s2.p1;
		clamp01(t1);
		t2 = 0.0f;
		return len;
	}

	/* �������m */

	// 2���������s�������琂���̒[�_�̈��P1�ɉ�����
	if (isParallel(s1.v, s2.v) == true) {
		t1 = 0.0f;
		p1 = s1.p1;
		float len = calcPointSegmentDist(s1.p1, s2, p2, t2);
		if (0.0f <= t2 && t2 <= 1.0f) {
			return len;
		}
	}
	else {
		// �����͂˂���̊֌W
		// 2�����Ԃ̍ŒZ���������߂ĉ���t1,t2�����߂�
		float len = calcLineLineDist(s1, s2, p1, p2, t1, t2);
		if (
			0.0f <= t1 && t1 <= 1.0f &&
			0.0f <= t2 && t2 <= 1.0f
			)
		{
			return len;
		}
	}

	// �����̑����O�ɂ��鎖������
	// S1����t1��0�`1�̊ԂɃN�����v���Đ������~�낷
	clamp01(t1);
	p1 = s1.getPoint(t1);
	float len = calcPointSegmentDist(p1, s2, p2, t2);
	if (0.0f <= t2 && t2 <= 1.0f) {
		return len;
	}

	// S2�����O�������̂�S2�����N�����v�AS1�ɐ������~�낷
	clamp01(t2);
	p2 = s2.getPoint(t2);
	len = calcPointSegmentDist(p2, s1, p1, t1);
	if (0.0f <= t1 && t1 <= 1.0f) {
		return len;
	}
	// �o���̒[�_���ŒZ�Ɣ���
	clamp01(t1);
	p1 = s1.getPoint(t1);
	return (p2 - p1).Length();
}


// �J�v�Z�����m�̏Փ˔���
// c1 : S1(����1)
// c2 : S2(����2)
// �߂�l: �Փ˂��Ă�����true
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
