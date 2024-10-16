#pragma once

#include "xr_vector.h"
#include "xr_string.h"

// STL extensions
#define DEF_VECTOR(N,T)				typedef xr_vector< T > N;		typedef N::iterator N##_it;
#define DEF_LIST(N,T)				typedef xr_list< T > N;			typedef N::iterator N##_it;
#define DEF_DEQUE(N,T)				typedef xr_deque< T > N;		typedef N::iterator N##_it;
#define DEF_MAP(N,K,T)				typedef xr_map< K, T > N;		typedef N::iterator N##_it;

#define DEFINE_DEQUE(T,N,I)			typedef xr_deque< T > N;		typedef N::iterator I;
#define DEFINE_LIST(T,N,I)			typedef xr_list< T > N;			typedef N::iterator I;
#define DEFINE_VECTOR(T,N,I)		typedef xr_vector< T > N;		typedef N::iterator I;
#define DEFINE_MAP(K,T,N,I)			typedef xr_map< K , T > N;		typedef N::iterator I;
#define DEFINE_MAP_PRED(K,T,N,I,P)	typedef xr_map< K, T, P > N;	typedef N::iterator I;
#define DEFINE_MMAP(K,T,N,I)		typedef xr_multimap< K, T > N;	typedef N::iterator I;
#define DEFINE_SVECTOR(T,C,N,I)		typedef svector< T, C > N;		typedef N::iterator I;
#define DEFINE_SET(T,N,I)			typedef xr_set< T > N;			typedef N::iterator I;
#define DEFINE_SET_PRED(T,N,I,P)	typedef xr_set< T, P > N;		typedef N::iterator I;
#define DEFINE_STACK(T,N)			typedef xr_stack< T > N;

// auxilary definition
DEFINE_VECTOR(bool, boolVec, boolIt);
DEFINE_VECTOR(BOOL, BOOLVec, BOOLIt);
DEFINE_VECTOR(BOOL*, LPBOOLVec, LPBOOLIt);
DEFINE_VECTOR(Frect, FrectVec, FrectIt);
DEFINE_VECTOR(Irect, IrectVec, IrectIt);
DEFINE_VECTOR(Fplane, PlaneVec, PlaneIt);
DEFINE_VECTOR(Fvector2, Fvector2Vec, Fvector2It);
DEFINE_VECTOR(Fvector, FvectorVec, FvectorIt);
DEFINE_VECTOR(Fvector*, LPFvectorVec, LPFvectorIt);
DEFINE_VECTOR(Fcolor, FcolorVec, FcolorIt);
DEFINE_VECTOR(Fcolor*, LPFcolorVec, LPFcolorIt);
DEFINE_VECTOR(LPSTR, LPSTRVec, LPSTRIt);
DEFINE_VECTOR(LPCSTR, LPCSTRVec, LPCSTRIt);
DEFINE_VECTOR(string64, string64Vec, string64It);
DEFINE_VECTOR(xr_string, SStringVec, SStringVecIt);

DEFINE_VECTOR(s8, S8Vec, S8It);
DEFINE_VECTOR(s8*, LPS8Vec, LPS8It);
DEFINE_VECTOR(s16, S16Vec, S16It);
DEFINE_VECTOR(s16*, LPS16Vec, LPS16It);
DEFINE_VECTOR(s32, S32Vec, S32It);
DEFINE_VECTOR(s32*, LPS32Vec, LPS32It);
DEFINE_VECTOR(u8, U8Vec, U8It);
DEFINE_VECTOR(u8*, LPU8Vec, LPU8It);
DEFINE_VECTOR(u16, U16Vec, U16It);
DEFINE_VECTOR(u16*, LPU16Vec, LPU16It);
DEFINE_VECTOR(u32, U32Vec, U32It);
DEFINE_VECTOR(u32*, LPU32Vec, LPU32It);
DEFINE_VECTOR(float, FloatVec, FloatIt);
DEFINE_VECTOR(float*, LPFloatVec, LPFloatIt);
DEFINE_VECTOR(int, IntVec, IntIt);
DEFINE_VECTOR(int*, LPIntVec, LPIntIt);
