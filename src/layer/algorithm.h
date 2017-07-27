// algorithm standard header
#pragma once
#ifndef _ALGORITHM_
#define _ALGORITHM_
#ifndef RC_INVOKED
#include <xmemory>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new
#pragma warning(disable: 4244)

_STD_BEGIN
// COMMON SORT PARAMETERS
const int _ISORT_MAX = 32;	// maximum size for insertion sort

// TEMPLATE FUNCTION for_each
template<class _InIt,
class _Fn1> inline
	void _For_each(_InIt _First, _InIt _Last, _Fn1& _Func)
{	// perform function for each element
	for (; _First != _Last; ++_First)
		_Func(*_First);
}

template<class _InIt,
class _Fn1> inline
	_Fn1 for_each(_InIt _First, _InIt _Last, _Fn1 _Func)
{	// perform function for each element
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Func);
	_For_each(_Unchecked(_First), _Unchecked(_Last), _Func);

	return (_STD move(_Func));
}

// TEMPLATE FUNCTION find_if
template<class _InIt,
class _Pr> inline
	_InIt _Find_if(_InIt _First, _InIt _Last, _Pr _Pred)
{	// find first satisfying _Pred
	for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			break;
	return (_First);
}

template<class _InIt,
class _Pr> inline
	_InIt find_if(_InIt _First, _InIt _Last, _Pr _Pred)
{	// find first satisfying _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Find_if(_Unchecked(_First), _Unchecked(_Last), _Pred)));
}

// TEMPLATE FUNCTION adjacent_find WITH PRED
template<class _FwdIt,
class _Pr> inline
	_FwdIt _Adjacent_find(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find first satisfying _Pred with successor
	if (_First != _Last)
		for (_FwdIt _Firstb; (_Firstb = _First), ++_First != _Last;)
			if (_Pred(*_Firstb, *_First))
				return (_Firstb);
	return (_Last);
}

template<class _FwdIt,
class _Pr> inline
	_FwdIt adjacent_find(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find first satisfying _Pred with successor
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Adjacent_find(_Unchecked(_First), _Unchecked(_Last), _Pred)));
}

// TEMPLATE FUNCTION adjacent_find
template<class _FwdIt> inline
_FwdIt adjacent_find(_FwdIt _First, _FwdIt _Last)
{	// find first matching successor
	return (_STD adjacent_find(_First, _Last, equal_to<>()));
}

// TEMPLATE FUNCTION count_if
template<class _InIt,
class _Pr> inline
	typename iterator_traits<_InIt>::difference_type
	_Count_if(_InIt _First, _InIt _Last, _Pr _Pred)
{	// count elements satisfying _Pred
	typename iterator_traits<_InIt>::difference_type _Count = 0;

	for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			++_Count;
	return (_Count);
}

template<class _InIt,
class _Pr> inline
	typename iterator_traits<_InIt>::difference_type
	count_if(_InIt _First, _InIt _Last, _Pr _Pred)
{	// count elements satisfying _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Count_if(_Unchecked(_First), _Unchecked(_Last), _Pred));
}

// TEMPLATE FUNCTION mismatch WITH PRED
template<class _InIt1,
class _InIt2,
class _Pr> inline
	pair<_InIt1, _InIt2>
	_Mismatch(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _Pr _Pred)
{	// return [_First1, _Last1)/[_First2, ...) mismatch using _Pred
	for (; _First1 != _Last1 && _Pred(*_First1, *_First2);)
		++_First1, ++_First2;
	return (pair<_InIt1, _InIt2>(_First1, _First2));
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt1,
class _InIt2,
class _Pr> inline
	pair<_InIt1, _InIt2>
	mismatch(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _Pr _Pred)
{	// return [_First1, _Last1)/[_First2, ...) mismatch using _Pred
	pair<_UNCHECKED_TYPE(_InIt1), _InIt2> _Ans(
		_Mismatch(_Unchecked(_First1), _Unchecked(_Last1),
		_First2, _Pred));
	return (pair<_InIt1, _InIt2>(
		_Rechecked(_First1, _Ans.first),
		_Ans.second));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt1,
class _InIt2,
class _Pr> inline
	pair<_InIt1, _InIt2>
	_Mismatch2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _Pr _Pred, true_type)
{	// return [_First1, _Last1)/[_First2, ...) mismatch, checked input
	return (_Mismatch(_First1, _Last1,
		_First2, _Pred));
}

template<class _InIt1,
class _InIt2,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	pair<_InIt1, _InIt2>
	_Mismatch2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _Pr _Pred, false_type)
{	// return [_First1, _Last1)/[_First2, ...) mismatch, unchecked input
	return (_Mismatch(_First1, _Last1,
		_First2, _Pred));
}

template<class _InIt1,
class _InIt2,
class _Pr> inline
	pair<_InIt1, _InIt2>
	mismatch(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _Pr _Pred)
{	// return [_First1, _Last1)/[_First2, ...) mismatch using _Pred
	_DEBUG_RANGE(_First1, _Last1);
	_DEBUG_POINTER(_First2);
	_DEBUG_POINTER(_Pred);
	pair<_UNCHECKED_TYPE(_InIt1), _InIt2> _Ans(
		_Mismatch2(_Unchecked(_First1), _Unchecked(_Last1),
		_First2, _Pred, _Is_checked(_First2)));
	return (pair<_InIt1, _InIt2>(
		_Rechecked(_First1, _Ans.first),
		_Ans.second));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InTy,
	size_t _InSize,
class _Pr> inline
	pair<_InIt1, _InTy *>
	mismatch(_InIt1 _First1, _InIt1 _Last1,
	_InTy(&_First2)[_InSize], _Pr _Pred)
{	// return [_First1, _Last1)/[_First2, ...) mismatch using _Pred
	pair<_InIt1, _Array_iterator<_InTy, _InSize> > _Ans(
		_STD mismatch(_First1, _Last1,
		_Array_iterator<_InTy, _InSize>(_First2), _Pred));
	return (pair<_InIt1, _InTy *>(
		_Ans.first,
		_Unchecked(_Ans.second)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION mismatch
template<class _InIt1,
class _InIt2> inline
	pair<_InIt1, _InIt2>
	mismatch(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2)
{	// return [_First1, _Last1)/[_First2, ...) mismatch
	return (_STD mismatch(_First1, _Last1, _First2,
		equal_to<>()));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InTy,
	size_t _InSize> inline
	pair<_InIt1, _InTy *>
	mismatch(_InIt1 _First1, _InIt1 _Last1,
	_InTy(&_First2)[_InSize])
{	// return [_First1, _Last1)/[_First2, ...) mismatch, array input
	return (_STD mismatch(_First1, _Last1, _First2,
		equal_to<>()));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */

// TEMPLATE FUNCTION all_of
template<class _InIt,
class _Pr> inline
	bool _All_of(_InIt _First, _InIt _Last, _Pr _Pred)
{	// test if all elements satisfy _Pred
	for (; _First != _Last; ++_First)
		if (!_Pred(*_First))
			return (false);
	return (true);
}

template<class _InIt,
class _Pr> inline
	bool all_of(_InIt _First, _InIt _Last, _Pr _Pred)
{	// test if all elements satisfy _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_All_of(_Unchecked(_First), _Unchecked(_Last), _Pred));
}

// TEMPLATE FUNCTION any_of
template<class _InIt,
class _Pr> inline
	bool _Any_of(_InIt _First, _InIt _Last, _Pr _Pred)
{	// test if any element satisfies _Pred
	for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			return (true);
	return (false);
}

template<class _InIt,
class _Pr> inline
	bool any_of(_InIt _First, _InIt _Last, _Pr _Pred)
{	// test if any element satisfies _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Any_of(_Unchecked(_First), _Unchecked(_Last), _Pred));
}

// TEMPLATE FUNCTION none_of
template<class _InIt,
class _Pr> inline
	bool _None_of(_InIt _First, _InIt _Last, _Pr _Pred)
{	// test if no elements satisfy _Pred
	for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			return (false);
	return (true);
}

template<class _InIt,
class _Pr> inline
	bool none_of(_InIt _First, _InIt _Last, _Pr _Pred)
{	// test if no elements satisfy _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_None_of(_Unchecked(_First), _Unchecked(_Last), _Pred));
}

// TEMPLATE FUNCTION find_if_not
template<class _InIt,
class _Pr> inline
	_InIt _Find_if_not(_InIt _First, _InIt _Last, _Pr _Pred)
{	// find first element that satisfies !_Pred
	for (; _First != _Last; ++_First)
		if (!_Pred(*_First))
			break;
	return (_First);
}

template<class _InIt,
class _Pr> inline
	_InIt find_if_not(_InIt _First, _InIt _Last, _Pr _Pred)
{	// find first element that satisfies !_Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Find_if_not(_Unchecked(_First), _Unchecked(_Last), _Pred)));
}

// TEMPLATE FUNCTION copy_if
template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt _Copy_if(_InIt _First, _InIt _Last, _OutIt _Dest,
	_Pr _Pred)
{	// copy each satisfying _Pred
	for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			*_Dest++ = *_First;
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt copy_if(_InIt _First, _InIt _Last, _OutIt _Dest,
	_Pr _Pred)
{	// copy each satisfying _Pred
	return (_Copy_if(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Pred));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt _Copy_if(_InIt _First, _InIt _Last, _OutIt _Dest,
	_Pr _Pred, true_type)
{	// copy each satisfying _Pred, checked dest
	return (_Copy_if(_First, _Last,
		_Dest, _Pred));
}

template<class _InIt,
class _OutIt,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Copy_if(_InIt _First, _InIt _Last, _OutIt _Dest,
	_Pr _Pred, false_type)
{	// copy each satisfying _Pred, unchecked dest
	return (_Copy_if(_First, _Last,
		_Dest, _Pred));
}

template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt copy_if(_InIt _First, _InIt _Last, _OutIt _Dest,
	_Pr _Pred)
{	// copy each satisfying _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	_DEBUG_POINTER(_Pred);
	return (_Copy_if(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Pred, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy,
	size_t _OutSize,
class _Pr> inline
	_OutTy *copy_if(_InIt _First, _InIt _Last, _OutTy(&_Dest)[_OutSize],
	_Pr _Pred)
{	// copy each satisfying _Pred, array dest
	return (_Unchecked(
		_STD copy_if(_First, _Last,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION partition_copy
template<class _InIt,
class _OutIt1,
class _OutIt2,
class _Pr> inline
	pair<_OutIt1, _OutIt2>
	_Partition_copy(_InIt _First, _InIt _Last,
	_OutIt1 _Dest1, _OutIt2 _Dest2, _Pr _Pred)
{	// copy true partition *_Dest1++, false to *_Dest2++
	for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			*_Dest1++ = *_First;
		else
			*_Dest2++ = *_First;
	return (pair<_OutIt1, _OutIt2>(_Dest1, _Dest2));
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt,
class _OutIt1,
class _OutIt2,
class _Pr> inline
	pair<_OutIt1, _OutIt2>
	partition_copy(_InIt _First, _InIt _Last,
	_OutIt1 _Dest1, _OutIt2 _Dest2, _Pr _Pred)
{	// copy true partition *_Dest1++, false to *_Dest2++
	return (pair<_OutIt1, _OutIt2>(
		_Partition_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest1, _Dest2, _Pred)));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt,
class _OutIt1,
class _OutIt2,
class _Pr> inline
	pair<_OutIt1, _OutIt2>
	_Partition_copy(_InIt _First, _InIt _Last,
	_OutIt1 _Dest1, _OutIt2 _Dest2, _Pr _Pred,
	true_type, true_type)
{	// copy true partition *_Dest1++, false to *_Dest2++, checked dest
	return (pair<_OutIt1, _OutIt2>(
		_Partition_copy(_First, _Last,
		_Dest1, _Dest2, _Pred)));
}

template<class _InIt,
class _OutIt1,
class _OutIt2,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	pair<_OutIt1, _OutIt2>
	_Partition_copy(_InIt _First, _InIt _Last,
	_OutIt1 _Dest1, _OutIt2 _Dest2, _Pr _Pred,
	true_type, false_type)
{	// copy true partition *_Dest1++, false to *_Dest2++, unchecked dest
	return (pair<_OutIt1, _OutIt2>(
		_Partition_copy(_First, _Last,
		_Dest1, _Dest2, _Pred)));
}

template<class _InIt,
class _OutIt1,
class _OutIt2,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	pair<_OutIt1, _OutIt2>
	_Partition_copy(_InIt _First, _InIt _Last,
	_OutIt1 _Dest1, _OutIt2 _Dest2, _Pr _Pred,
	false_type, true_type)
{	// copy true partition *_Dest1++, false to *_Dest2++, unchecked dest
	return (pair<_OutIt1, _OutIt2>(
		_Partition_copy(_First, _Last,
		_Dest1, _Dest2, _Pred)));
}

template<class _InIt,
class _OutIt1,
class _OutIt2,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	pair<_OutIt1, _OutIt2>
	_Partition_copy(_InIt _First, _InIt _Last,
	_OutIt1 _Dest1, _OutIt2 _Dest2, _Pr _Pred,
	false_type, false_type)
{	// copy true partition *_Dest1++, false to *_Dest2++, unchecked dest
	return (pair<_OutIt1, _OutIt2>(
		_Partition_copy(_First, _Last,
		_Dest1, _Dest2, _Pred)));
}

template<class _InIt,
class _OutIt1,
class _OutIt2,
class _Pr> inline
	pair<_OutIt1, _OutIt2>
	partition_copy(_InIt _First, _InIt _Last,
	_OutIt1 _Dest1, _OutIt2 _Dest2, _Pr _Pred)
{	// copy true partition *_Dest1++, false to *_Dest2++
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest1);
	_DEBUG_POINTER(_Dest2);
	_DEBUG_POINTER(_Pred);
	return (pair<_OutIt1, _OutIt2>(
		_Partition_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest1, _Dest2, _Pred,
		_Is_checked(_Dest1), _Is_checked(_Dest2))));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy1,
	size_t _OutSize1,
class _OutIt2,
class _Pr> inline
	pair<_OutTy1 *, _OutIt2>
	partition_copy(_InIt _First, _InIt _Last,
	_OutTy1(&_Dest1)[_OutSize1], _OutIt2 _Dest2, _Pr _Pred)
{	// copy true partition *_Dest1++, false to *_Dest2++, array dest
	pair<_Array_iterator<_OutTy1, _OutSize1>, _OutIt2> _Ans =
		_STD partition_copy(_First, _Last,
		_Array_iterator<_OutTy1, _OutSize1>(_Dest1), _Dest2, _Pred);
	return (pair<_OutTy1 *, _OutIt2>(
		_Unchecked(_Ans.first),
		_Ans.second));
}

template<class _InIt,
class _OutIt1,
class _OutTy2,
	size_t _OutSize2,
class _Pr> inline
	pair<_OutIt1, _OutTy2 *>
	partition_copy(_InIt _First, _InIt _Last,
	_OutIt1 _Dest1, _OutTy2(&_Dest2)[_OutSize2], _Pr _Pred)
{	// copy true partition *_Dest1++, false to *_Dest2++, array dest
	pair<_OutIt1, _Array_iterator<_OutTy2, _OutSize2> > _Ans =
		_STD partition_copy(_First, _Last,
		_Dest1, _Array_iterator<_OutTy2, _OutSize2>(_Dest2), _Pred);
	return (pair<_OutIt1, _OutTy2 *>(
		_Ans.first,
		_Unchecked(_Ans.second)));
}

template<class _InIt,
class _OutTy1,
	size_t _OutSize1,
class _OutTy2,
	size_t _OutSize2,
class _Pr> inline
	pair<_OutTy1 *, _OutTy2 *>
	partition_copy(_InIt _First, _InIt _Last,
	_OutTy1(&_Dest1)[_OutSize1], _OutTy2(&_Dest2)[_OutSize2],
	_Pr _Pred)
{	// copy true partition *_Dest1++, false to *_Dest2++, array dest
	pair<_Array_iterator<_OutTy1, _OutSize1>,
		_Array_iterator<_OutTy2, _OutSize2> > _Ans =
		_STD partition_copy(_First, _Last,
		_Array_iterator<_OutTy1, _OutSize1>(_Dest1),
		_Array_iterator<_OutTy2, _OutSize2>(_Dest2), _Pred);
	return (pair<_OutTy1 *, _OutTy2 *>(
		_Unchecked(_Ans.first),
		_Unchecked(_Ans.second)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION is_partitioned
template<class _InIt,
class _Pr> inline
	bool _Is_partitioned(_InIt _First, _InIt _Last, _Pr _Pred)
{	// test if [_First, _Last) partitioned by _Pred
	for (; _First != _Last; ++_First)
		if (!_Pred(*_First))
			break;	// skip true partition
	for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			return (false);	// found out of place element
	return (true);
}

template<class _InIt,
class _Pr> inline
	bool is_partitioned(_InIt _First, _InIt _Last, _Pr _Pred)
{	// test if [_First, _Last) partitioned by _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Is_partitioned(_Unchecked(_First), _Unchecked(_Last),
		_Pred));
}

// TEMPLATE FUNCTION partition_point
template<class _FwdIt,
class _Diff,
class _Pr> inline
	_FwdIt _Partition_point(_FwdIt _First, _FwdIt _Last, _Pr _Pred, _Diff *)
{	// find beginning of false partition in [_First, _Last)
	_Diff _Count = 0;
	_Distance(_First, _Last, _Count);
	while (0 < _Count)
	{	// divide and conquer, find half that contains answer
		_Diff _Count2 = _Count / 2;
		_FwdIt _Mid = _First;
		_STD advance(_Mid, _Count2);

		if (_Pred(*_Mid))
		{	// try top half
			_First = ++_Mid;
			_Count -= _Count2 + 1;
		}
		else
			_Count = _Count2;
	}
	return (_First);
}

template<class _FwdIt,
class _Pr> inline
	_FwdIt partition_point(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find beginning of false partition in [_First, _Last)
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Partition_point(_Unchecked(_First), _Unchecked(_Last), _Pred,
		_Dist_type(_First))));
}

// TEMPLATE FUNCTION search WITH PRED
template<class _FwdIt1,
class _FwdIt2,
class _Diff1,
class _Diff2,
class _Pr> inline
	_FwdIt1 _Search(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2, _Pr _Pred, _Diff1 *, _Diff2 *)
{	// find first [_First2, _Last2) satisfying _Pred
	_Diff1 _Count1 = 0;
	_Distance(_First1, _Last1, _Count1);
	_Diff2 _Count2 = 0;
	_Distance(_First2, _Last2, _Count2);

	for (; _Count2 <= _Count1; ++_First1, --_Count1)
	{	// room for match, try it
		_FwdIt1 _Mid1 = _First1;
		for (_FwdIt2 _Mid2 = _First2;; ++_Mid1, ++_Mid2)
			if (_Mid2 == _Last2)
				return (_First1);
			else if (!_Pred(*_Mid1, *_Mid2))
				break;
	}
	return (_Last1);
}

template<class _FwdIt1,
class _FwdIt2,
class _Pr> inline
	_FwdIt1 search(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2, _Pr _Pred)
{	// find first [_First2, _Last2) satisfying _Pred
	_DEBUG_RANGE(_First1, _Last1);
	_DEBUG_RANGE(_First2, _Last2);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First1,
		_Search(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2), _Pred,
		_Dist_type(_First1), _Dist_type(_First2))));
}

// TEMPLATE FUNCTION search
template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt1 search(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2)
{	// find first [_First2, _Last2) match
	return (_STD search(_First1, _Last1, _First2, _Last2,
		equal_to<>()));
}

// TEMPLATE FUNCTION search_n WITH PRED
template<class _FwdIt1,
class _Diff2,
class _Ty,
class _Pr> inline
	_FwdIt1 _Search_n(_FwdIt1 _First1, _FwdIt1 _Last1,
	_Diff2 _Count, const _Ty& _Val, _Pr _Pred, forward_iterator_tag)
{	// find first _Count * _Val satisfying _Pred, forward iterators
	if (_Count <= 0)
		return (_First1);

	for (; _First1 != _Last1; ++_First1)
		if (_Pred(*_First1, _Val))
		{	// found start of possible match, check it out
		_FwdIt1 _Mid1 = _First1;

		for (_Diff2 _Count1 = _Count;;)
			if (--_Count1 == 0)
				return (_First1);	// found rest of match, report it
			else if (++_Mid1 == _Last1)
				return (_Last1);	// short match at end
			else if (!_Pred(*_Mid1, _Val))
			{	// short match not at end
				break;
			}

			_First1 = _Mid1;	// pick up just beyond failed match
		}
	return (_Last1);
}

template<class _FwdIt1,
class _Diff2,
class _Ty,
class _Pr> inline
	_FwdIt1 _Search_n(_FwdIt1 _First1, _FwdIt1 _Last1,
	_Diff2 _Count, const _Ty& _Val, _Pr _Pred, random_access_iterator_tag)
{	// find first _Count * _Val satisfying _Pred, random-access iterators
	if (_Count <= 0)
		return (_First1);

	_FwdIt1 _Oldfirst1 = _First1;
	for (_Diff2 _Inc = 0; _Count <= _Last1 - _Oldfirst1;)
	{	// enough room, look for a match
		_First1 = _Oldfirst1 + _Inc;
		if (_Pred(*_First1, _Val))
		{	// found part of possible match, check it out
			_Diff2 _Count1 = _Count;
			_FwdIt1 _Mid1 = _First1;

			for (; _Oldfirst1 != _First1 && _Pred(_First1[-1], _Val);
				--_First1)
				--_Count1;	// back up over any skipped prefix

			if (_Count1 <= _Last1 - _Mid1)
				for (;;)
				{	// enough left, test suffix
				if (--_Count1 == 0)
					return (_First1);	// found rest of match, report it
				else if (!_Pred(*++_Mid1, _Val))
				{	// short match not at end
					break;
				}
				}
			_Oldfirst1 = ++_Mid1;	// failed match, take small jump
			_Inc = 0;
		}
		else
		{	// no match, take big jump and back up as needed
			_Oldfirst1 = _First1 + 1;
			_Inc = _Count - 1;
		}
	}
	return (_Last1);
}

template<class _FwdIt1,
class _Diff2,
class _Ty,
class _Pr> inline
	_FwdIt1 search_n(_FwdIt1 _First1, _FwdIt1 _Last1,
	_Diff2 _Count, const _Ty& _Val, _Pr _Pred)
{	// find first _Count * _Val satisfying _Pred
	_DEBUG_RANGE(_First1, _Last1);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First1,
		_Search_n(_Unchecked(_First1), _Unchecked(_Last1), _Count, _Val,
		_Pred, _Iter_cat(_First1))));
}

// TEMPLATE FUNCTION search_n
template<class _FwdIt1,
class _Diff2,
class _Ty> inline
	_FwdIt1 search_n(_FwdIt1 _First1, _FwdIt1 _Last1,
	_Diff2 _Count, const _Ty& _Val)
{	// find first _Count * _Val match
	return (_STD search_n(_First1, _Last1, _Count, _Val,
		equal_to<>()));
}

// TEMPLATE FUNCTION find_end WITH PRED
template<class _FwdIt1,
class _FwdIt2,
class _Diff1,
class _Diff2,
class _Pr> inline
	_FwdIt1 _Find_end(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2, _Pr _Pred, _Diff1 *, _Diff2 *)
{	// find last [_First2, _Last2) satisfying _Pred
	_Diff1 _Count1 = 0;
	_Distance(_First1, _Last1, _Count1);
	_Diff2 _Count2 = 0;
	_Distance(_First2, _Last2, _Count2);
	_FwdIt1 _Ans = _Last1;

	if (0 < _Count2)
		for (; _Count2 <= _Count1; ++_First1, --_Count1)
		{	// room for match, try it
		_FwdIt1 _Mid1 = _First1;
		for (_FwdIt2 _Mid2 = _First2;; ++_Mid1)
			if (!_Pred(*_Mid1, *_Mid2))
				break;
			else if (++_Mid2 == _Last2)
			{	// potential answer, save it
				_Ans = _First1;
				break;
			}
		}
	return (_Ans);
}

template<class _FwdIt1,
class _FwdIt2,
class _Pr> inline
	_FwdIt1 find_end(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2, _Pr _Pred)
{	// find last [_First2, _Last2) satisfying _Pred
	_DEBUG_RANGE(_First1, _Last1);
	_DEBUG_RANGE(_First2, _Last2);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First1,
		_Find_end(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2), _Pred,
		_Dist_type(_First1), _Dist_type(_First2))));
}

// TEMPLATE FUNCTION find_end
template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt1 find_end(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2)
{	// find last [_First2, _Last2) match
	return (_STD find_end(_First1, _Last1, _First2, _Last2,
		equal_to<>()));
}

// TEMPLATE FUNCTION find_first_of WITH PRED
template<class _FwdIt1,
class _FwdIt2,
class _Pr> inline
	_FwdIt1 _Find_first_of(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2, _Pr _Pred)
{	// look for one of [_First2, _Last2) satisfying _Pred with element
	for (; _First1 != _Last1; ++_First1)
		for (_FwdIt2 _Mid2 = _First2; _Mid2 != _Last2; ++_Mid2)
			if (_Pred(*_First1, *_Mid2))
				return (_First1);
	return (_First1);
}

template<class _FwdIt1,
class _FwdIt2,
class _Pr> inline
	_FwdIt1 find_first_of(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2, _Pr _Pred)
{	// look for one of [_First2, _Last2) satisfying _Pred with element
	_DEBUG_RANGE(_First1, _Last1);
	_DEBUG_RANGE(_First2, _Last2);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First1,
		_Find_first_of(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2), _Pred)));
}

// TEMPLATE FUNCTION find_first_of
template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt1 find_first_of(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _First2, _FwdIt2 _Last2)
{	// look for one of [_First2, _Last2) that matches element
	return (_STD find_first_of(_First1, _Last1, _First2, _Last2,
		equal_to<>()));
}

// TEMPLATE FUNCTION swap_ranges
template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt2 _Swap_ranges(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _Dest)
{	// swap [_First1, _Last1) with [_Dest, ...)
	for (; _First1 != _Last1; ++_First1, ++_Dest)
		_STD iter_swap(_First1, _Dest);
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt2 swap_ranges(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _Dest)
{	// swap [_First1, _Last1) with [_Dest, ...)
	return (_Swap_ranges(_Unchecked(_First1), _Unchecked(_Last1),
		_Dest));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt2 _Swap_ranges(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _Dest,
	forward_iterator_tag, forward_iterator_tag)
{	// swap [_First1, _Last1) with [_Dest, ...), arbitrary iterators
	return (_Swap_ranges(_First1, _Last1,
		_Dest));
}

template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt2 _Swap_ranges(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _Dest,
	random_access_iterator_tag, random_access_iterator_tag)
{	// swap [_First1, _Last1) with [_Dest, ...), random-access iterators
	_FwdIt2 _Ans = _Dest + (_Last1 - _First1);	// also checks range
	_Swap_ranges(_First1, _Last1,
		_Unchecked(_Dest));
	return (_Ans);
}

template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt2 _Swap_ranges(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _Dest, true_type)
{	// swap [_First1, _Last1) with [_Dest, ...), checked dest
	return (_Swap_ranges(_First1, _Last1,
		_Dest, _Iter_cat(_First1), _Iter_cat(_Dest)));
}

template<class _FwdIt1,
class _FwdIt2> inline
	_SCL_INSECURE_DEPRECATE
	_FwdIt2 _Swap_ranges(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _Dest, false_type)
{	// swap [_First1, _Last1) with [_Dest, ...), unchecked dest
	return (_Swap_ranges(_First1, _Last1,
		_Dest, _Iter_cat(_First1), _Iter_cat(_Dest)));
}

template<class _FwdIt1,
class _FwdIt2> inline
	_FwdIt2 swap_ranges(_FwdIt1 _First1, _FwdIt1 _Last1,
	_FwdIt2 _Dest)
{	// swap [_First1, _Last1) with [_Dest, ...)
	_DEBUG_RANGE(_First1, _Last1);
	_DEBUG_POINTER(_Dest);
	return (_Swap_ranges(_Unchecked(_First1), _Unchecked(_Last1),
		_Dest, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _FwdIt1,
class _OutTy,
	size_t _OutSize> inline
	_OutTy *swap_ranges(_FwdIt1 _First1, _FwdIt1 _Last1,
	_OutTy(&_Dest)[_OutSize])
{	// swap [_First1, _Last1) with [_Dest, ...), array dest
	return (_Unchecked(
		_STD swap_ranges(_First1, _Last1,
		_Array_iterator<_OutTy, _OutSize>(_Dest))));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION transform WITH UNARY OP
template<class _InIt,
class _OutIt,
class _Fn1> inline
	_OutIt _Transform(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Fn1 _Func)
{	// transform [_First, _Last) with _Func
	for (; _First != _Last; ++_First, ++_Dest)
		*_Dest = _Func(*_First);
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt,
class _OutIt,
class _Fn1> inline
	_OutIt transform(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Fn1 _Func)
{	// transform [_First, _Last) with _Func
	if (_First != _Last)
		return (_Transform(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Func));
	return (_Dest);
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt,
class _OutIt,
class _Fn1> inline
	_OutIt _Transform1(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Fn1 _Func,
	input_iterator_tag, _Mutable_iterator_tag)
{	// transform [_First, _Last) with _Func, arbitrary iterators
	return (_Transform(_First, _Last,
		_Dest, _Func));
}

template<class _InIt,
class _OutIt,
class _Fn1> inline
	_OutIt _Transform1(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Fn1 _Func,
	random_access_iterator_tag, random_access_iterator_tag)
{	// transform [_First, _Last) with _Func, random-access iterators
	_OutIt _Ans = _Dest + (_Last - _First);	// also checks range
	_Transform(_First, _Last,
		_Unchecked(_Dest), _Func);
	return (_Ans);
}

template<class _InIt,
class _OutIt,
class _Fn1> inline
	_OutIt _Transform1(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Fn1 _Func, true_type)
{	// transform [_First, _Last) with _Func, checked dest
	return (_Transform1(_First, _Last,
		_Dest, _Func,
		_Iter_cat(_First), _Iter_cat(_Dest)));
}

template<class _InIt,
class _OutIt,
class _Fn1> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Transform1(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Fn1 _Func, false_type)
{	// transform [_First, _Last) with _Func, unchecked dest
	return (_Transform1(_First, _Last,
		_Dest, _Func,
		_Iter_cat(_First), _Iter_cat(_Dest)));
}

template<class _InIt,
class _OutIt,
class _Fn1> inline
	_OutIt transform(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Fn1 _Func)
{	// transform [_First, _Last) with _Func
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	_DEBUG_POINTER(_Func);
	if (_First != _Last)
		return (_Transform1(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Func, _Is_checked(_Dest)));
	return (_Dest);
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy,
	size_t _OutSize,
class _Fn1> inline
	_OutTy *transform(_InIt _First, _InIt _Last,
	_OutTy(&_Dest)[_OutSize], _Fn1 _Func)
{	// transform [_First, _Last) with _Func, array dest
	return (_Unchecked(
		_STD transform(_First, _Last,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Func)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION transform WITH BINARY OP
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_OutIt _Transform(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func)
{	// transform [_First1, _Last1) and [_First2, ...) with _Func
	for (; _First1 != _Last1; ++_First1, ++_First2, ++_Dest)
		*_Dest = _Func(*_First1, *_First2);
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_OutIt transform(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func)
{	// transform [_First1, _Last1) and [_First2, ...) with _Func
	if (_First1 != _Last1)
		return (_Transform(_Unchecked(_First1), _Unchecked(_Last1),
		_First2, _Dest, _Func));
	return (_Dest);
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_OutIt _Transform3(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func,
	input_iterator_tag, _Mutable_iterator_tag)
{	// transform [_First1, _Last1) and [_First2, ...), arbitrary dest
	return (_Transform(_First1, _Last1,
		_First2, _Dest, _Func));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_OutIt _Transform3(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func,
	random_access_iterator_tag, random_access_iterator_tag)
{	// transform [_First1, _Last1) and [_First2, ...), random-access dest
	_OutIt _Ans = _Dest + (_Last1 - _First1);	// also checks range
	_Transform(_First1, _Last1,
		_First2, _Unchecked(_Dest), _Func);
	return (_Ans);
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_OutIt _Transform2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func,
	input_iterator_tag, input_iterator_tag)
{	// transform [_First1, _Last1) and [_First2, ...), arbitrary input
	return (_Transform3(_First1, _Last1,
		_First2, _Dest, _Func,
		_Iter_cat(_First1), _Iter_cat(_Dest)));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_OutIt _Transform2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func,
	random_access_iterator_tag, random_access_iterator_tag)
{	// transform [_First1, _Last1) and [_First2, ...), random-access input
	_InIt2 _Last2 = _First2 + (_Last1 - _First1);	// also checks range
	_Last2 = _Last2;	// to quiet diagnostics
	return (_Transform3(_First1, _Last1,
		_Unchecked(_First2), _Dest, _Func,
		_Iter_cat(_First1), _Iter_cat(_Dest)));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_OutIt _Transform2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func,
	true_type)
{	// transform [_First1, _Last1) and [_First2, ...), checked dest
	return (_Transform2(_First1, _Last1,
		_First2, _Dest, _Func,
		_Iter_cat(_First1), _Iter_cat(_First2)));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Transform2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func,
	false_type)
{	// transform [_First1, _Last1) and [_First2, ...), unchecked dest
	return (_Transform2(_First1, _Last1,
		_First2, _Dest, _Func,
		_Iter_cat(_First1), _Iter_cat(_First2)));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Fn2> inline
	_OutIt transform(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func)
{	// transform [_First1, _Last1) and [_First2, ...) with _Func
	_DEBUG_RANGE(_First1, _Last1);
	_DEBUG_POINTER(_Dest);
	_DEBUG_POINTER(_Func);
	if (_First1 != _Last1)
		return (_Transform2(_Unchecked(_First1), _Unchecked(_Last1),
		_First2, _Dest, _Func,
		_Is_checked(_Dest)));
	return (_Dest);
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InTy,
	size_t _InSize,
class _OutIt,
class _Fn2> inline
	_OutIt transform(_InIt1 _First1, _InIt1 _Last1,
	_InTy(&_First2)[_InSize], _OutIt _Dest, _Fn2 _Func)
{	// transform [_First1, _Last1) and [_First2, ...), array input
	return (_STD transform(_First1, _Last1,
		_Array_iterator<_InTy, _InSize>(_First2), _Dest, _Func));
}

template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize,
class _Fn2> inline
	_OutTy *transform(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutTy(&_Dest)[_OutSize], _Fn2 _Func)
{	// transform [_First1, _Last1) and [_First2, ...), array dest
	return (_Unchecked(
		_STD transform(_First1, _Last1,
		_First2, _Array_iterator<_OutTy, _OutSize>(_Dest), _Func)));
}

template<class _InIt1,
class _InTy,
	size_t _InSize,
class _OutTy,
	size_t _OutSize,
class _Fn2> inline
	_OutTy *transform(_InIt1 _First1, _InIt1 _Last1,
	_InTy(&_First2)[_InSize], _OutTy(&_Dest)[_OutSize], _Fn2 _Func)
{	// transform [_First1, _Last1) and [_First2, ...), array input/dest
	return (_Unchecked(
		_STD transform(_First1, _Last1,
		_Array_iterator<_InTy, _InSize>(_First2),
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Func)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION replace
template<class _FwdIt,
class _Ty> inline
	void _Replace(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Oldval, const _Ty& _Newval)
{	// replace each matching _Oldval with _Newval
	for (; _First != _Last; ++_First)
		if (*_First == _Oldval)
			*_First = _Newval;
}

template<class _FwdIt,
class _Ty> inline
	void replace(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Oldval, const _Ty& _Newval)
{	// replace each matching _Oldval with _Newval
	_DEBUG_RANGE(_First, _Last);
	_Replace(_Unchecked(_First), _Unchecked(_Last),
		_Oldval, _Newval);
}

// TEMPLATE FUNCTION replace_if
template<class _FwdIt,
class _Pr,
class _Ty> inline
	void _Replace_if(_FwdIt _First, _FwdIt _Last, _Pr _Pred, const _Ty& _Val)
{	// replace each satisfying _Pred with _Val
	for (; _First != _Last; ++_First)
		if (_Pred(*_First))
			*_First = _Val;
}

template<class _FwdIt,
class _Pr,
class _Ty> inline
	void replace_if(_FwdIt _First, _FwdIt _Last, _Pr _Pred, const _Ty& _Val)
{	// replace each satisfying _Pred with _Val
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	_Replace_if(_Unchecked(_First), _Unchecked(_Last),
		_Pred, _Val);
}

// TEMPLATE FUNCTION replace_copy
template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt _Replace_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Oldval, const _Ty& _Newval)
{	// copy replacing each matching _Oldval with _Newval
	for (; _First != _Last; ++_First, ++_Dest)
		*_Dest = *_First == _Oldval ? _Newval : *_First;
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt replace_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Oldval, const _Ty& _Newval)
{	// copy replacing each matching _Oldval with _Newval
	return (_Replace_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Oldval, _Newval));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt _Replace_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Oldval, const _Ty& _Newval,
	input_iterator_tag, _Mutable_iterator_tag)
{	// copy replacing each matching _Oldval, arbitrary iterators
	return (_Replace_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Oldval, _Newval));
}

template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt _Replace_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Oldval, const _Ty& _Newval,
	random_access_iterator_tag, random_access_iterator_tag)
{	// copy replacing each matching _Oldval, random-access iterators
	_OutIt _Ans = _Dest + (_Last - _First);	// also checks range
	_Replace_copy(_First, _Last,
		_Unchecked(_Dest), _Oldval, _Newval);
	return (_Ans);
}

template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt _Replace_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Oldval, const _Ty& _Newval,
	true_type)
{	// copy replacing each matching _Oldval with _Newval, checked dest
	return (_Replace_copy(_First, _Last,
		_Dest, _Oldval, _Newval,
		_Iter_cat(_First), _Iter_cat(_Dest)));
}

template<class _InIt,
class _OutIt,
class _Ty> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Replace_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Oldval, const _Ty& _Newval,
	false_type)
{	// copy replacing each matching _Oldval with _Newval, unchecked dest
	return (_Replace_copy(_First, _Last,
		_Dest, _Oldval, _Newval,
		_Iter_cat(_First), _Iter_cat(_Dest)));
}

template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt replace_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Oldval, const _Ty& _Newval)
{	// copy replacing each matching _Oldval with _Newval
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	return (_Replace_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Oldval, _Newval,
		_Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy,
	size_t _OutSize,
class _Ty> inline
	_OutTy *replace_copy(_InIt _First, _InIt _Last,
	_OutTy(&_Dest)[_OutSize], const _Ty& _Oldval, const _Ty& _Newval)
{	// copy replacing each matching _Oldval with _Newval, array dest
	return (_Unchecked(
		_STD replace_copy(_First, _Last,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Oldval, _Newval)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION replace_copy_if
template<class _InIt,
class _OutIt,
class _Pr,
class _Ty> inline
	_OutIt _Replace_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, const _Ty& _Val)
{	// copy replacing each satisfying _Pred with _Val
	for (; _First != _Last; ++_First, ++_Dest)
		*_Dest = _Pred(*_First) ? _Val : *_First;
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt,
class _OutIt,
class _Pr,
class _Ty> inline
	_OutIt replace_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, const _Ty& _Val)
{	// copy replacing each satisfying _Pred with _Val
	return (_Replace_copy_if(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Pred, _Val));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt,
class _OutIt,
class _Pr,
class _Ty> inline
	_OutIt _Replace_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, const _Ty& _Val,
	input_iterator_tag, _Mutable_iterator_tag)
{	// copy replacing each satisfying _Pred, arbitrary iterators
	return (_Replace_copy_if(_First, _Last,
		_Dest, _Pred, _Val));
}

template<class _InIt,
class _OutIt,
class _Pr,
class _Ty> inline
	_OutIt _Replace_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, const _Ty& _Val,
	random_access_iterator_tag, random_access_iterator_tag)
{	// copy replacing each satisfying _Pred, random-access iterators
	_OutIt _Ans = _Dest + (_Last - _First);	// also checks range
	_Replace_copy_if(_First, _Last,
		_Unchecked(_Dest), _Pred, _Val);
	return (_Ans);
}

template<class _InIt,
class _OutIt,
class _Pr,
class _Ty> inline
	_OutIt _Replace_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, const _Ty& _Val,
	true_type)
{	// copy replacing each satisfying _Pred with _Val, checked dest
	return (_Replace_copy_if(_First, _Last,
		_Dest, _Pred, _Val,
		_Iter_cat(_First), _Iter_cat(_Dest)));
}

template<class _InIt,
class _OutIt,
class _Pr,
class _Ty> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Replace_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, const _Ty& _Val,
	false_type)
{	// copy replacing each satisfying _Pred with _Val, unchecked dest
	return (_Replace_copy_if(_First, _Last,
		_Dest, _Pred, _Val,
		_Iter_cat(_First), _Iter_cat(_Dest)));
}

template<class _InIt,
class _OutIt,
class _Pr,
class _Ty> inline
	_OutIt replace_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, const _Ty& _Val)
{	// copy replacing each satisfying _Pred with _Val
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	_DEBUG_POINTER(_Pred);
	return (_Replace_copy_if(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Pred, _Val,
		_Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy,
	size_t _OutSize,
class _Pr,
class _Ty> inline
	_OutTy *replace_copy_if(_InIt _First, _InIt _Last,
	_OutTy(&_Dest)[_OutSize], _Pr _Pred, const _Ty& _Val)
{	// copy replacing each satisfying _Pred with _Val, array dest
	return (_Unchecked(
		_STD replace_copy_if(_First, _Last,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred, _Val)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION generate
template<class _FwdIt,
class _Fn0> inline
	void _Generate(_FwdIt _First, _FwdIt _Last, _Fn0 _Func)
{	// replace [_First, _Last) with _Func()
	for (; _First != _Last; ++_First)
		*_First = _Func();
}

template<class _FwdIt,
class _Fn0> inline
	void generate(_FwdIt _First, _FwdIt _Last, _Fn0 _Func)
{	// replace [_First, _Last) with _Func()
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Func);
	_Generate(_Unchecked(_First), _Unchecked(_Last), _Func);
}

// TEMPLATE FUNCTION generate_n
template<class _OutIt,
class _Diff,
class _Fn0> inline
	_OutIt _Generate_n(_OutIt _Dest, _Diff _Count, _Fn0 _Func)
{	// replace [_Dest, _Dest + _Count) with _Func()
	for (; 0 < _Count; --_Count, ++_Dest)
		*_Dest = _Func();
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _OutIt,
class _Diff,
class _Fn0> inline
	_OutIt generate_n(_OutIt _Dest, _Diff _Count, _Fn0 _Func)
{	// replace [_Dest, _Dest + _Count) with _Func()
	return (_Generate_n(_Dest, _Count, _Func));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _OutIt,
class _Diff,
class _Fn0> inline
	_OutIt _Generate_n1(_OutIt _Dest, _Diff _Count, _Fn0 _Func,
	_Mutable_iterator_tag)
{	// replace [_Dest, _Dest + _Count), arbitrary iterators
	return (_Generate_n(_Dest, _Count, _Func));
}

template<class _OutIt,
class _Diff,
class _Fn0> inline
	_OutIt _Generate_n1(_OutIt _Dest, _Diff _Count, _Fn0 _Func,
	random_access_iterator_tag)
{	// replace [_Dest, _Dest + _Count), random-access iterators
	_OutIt _Ans = _Dest + _Count;	// also checks range
	_Ans = _Ans;	// to quiet diagnostics
	return (_Rechecked(_Dest,
		_Generate_n(_Unchecked(_Dest), _Count, _Func)));
}

template<class _OutIt,
class _Diff,
class _Fn0> inline
	_OutIt _Generate_n(_OutIt _Dest, _Diff _Count, _Fn0 _Func,
	true_type)
{	// replace [_Dest, _Dest + _Count) with _Func(), checked dest
	return (_Generate_n1(_Dest, _Count, _Func,
		_Iter_cat(_Dest)));
}

template<class _OutIt,
class _Diff,
class _Fn0> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Generate_n(_OutIt _Dest, _Diff _Count, _Fn0 _Func,
	false_type)
{	// replace [_Dest, _Dest + _Count) with _Func(), unchecked dest
	return (_Generate_n1(_Dest, _Count, _Func,
		_Iter_cat(_Dest)));
}

template<class _OutIt,
class _Diff,
class _Fn0> inline
	_OutIt generate_n(_OutIt _Dest, _Diff _Count, _Fn0 _Func)
{	// replace [_Dest, _Dest + _Count) with _Func()
	_DEBUG_POINTER(_Dest);
	_DEBUG_POINTER(_Func);
	return (_Generate_n(_Dest, _Count, _Func,
		_Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _OutTy,
	size_t _OutSize,
class _Diff,
class _Fn0> inline
	_OutTy *generate_n(_OutTy(&_Dest)[_OutSize], _Diff _Count, _Fn0 _Func)
{	// replace [_Dest, _Dest + _Count) with _Func(), array dest
	return (_Unchecked(
		_STD generate_n(_Array_iterator<_OutTy, _OutSize>(_Dest),
		_Count, _Func)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION remove_copy
template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt _Remove_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Val)
{	// copy omitting each matching _Val
	for (; _First != _Last; ++_First)
		if (!(*_First == _Val))
			*_Dest++ = *_First;
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt remove_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Val)
{	// copy omitting each matching _Val
	return (_Remove_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Val));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt _Remove_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Val,
	true_type)
{	// copy omitting each matching _Val, checked dest
	return (_Remove_copy(_First, _Last,
		_Dest, _Val));
}

template<class _InIt,
class _OutIt,
class _Ty> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Remove_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Val,
	false_type)
{	// copy omitting each matching _Val, unchecked dest
	return (_Remove_copy(_First, _Last,
		_Dest, _Val));
}

template<class _InIt,
class _OutIt,
class _Ty> inline
	_OutIt remove_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, const _Ty& _Val)
{	// copy omitting each matching _Val
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	return (_Remove_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Val,
		_Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy,
	size_t _OutSize,
class _Ty> inline
	_OutTy *remove_copy(_InIt _First, _InIt _Last,
	_OutTy(&_Dest)[_OutSize], const _Ty& _Val)
{	// copy omitting each matching _Val, array dest
	return (_Unchecked(
		_STD remove_copy(_First, _Last,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Val)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION remove_copy_if
template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt _Remove_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred)
{	// copy omitting each element satisfying _Pred
	for (; _First != _Last; ++_First)
		if (!_Pred(*_First))
			*_Dest++ = *_First;
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt remove_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred)
{	// copy omitting each element satisfying _Pred
	return (_Remove_copy_if(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Pred));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt _Remove_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred,
	true_type)
{	// copy omitting each element satisfying _Pred, checked dest
	return (_Remove_copy_if(_First, _Last,
		_Dest, _Pred));
}

template<class _InIt,
class _OutIt,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Remove_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred,
	false_type)
{	// copy omitting each element satisfying _Pred, unchecked dest
	return (_Remove_copy_if(_First, _Last,
		_Dest, _Pred));
}

template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt remove_copy_if(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred)
{	// copy omitting each element satisfying _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	_DEBUG_POINTER(_Pred);
	return (_Remove_copy_if(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Pred,
		_Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy,
	size_t _OutSize,
class _Pr> inline
	_OutTy *remove_copy_if(_InIt _First, _InIt _Last,
	_OutTy(&_Dest)[_OutSize], _Pr _Pred)
{	// copy omitting each element satisfying _Pred, array dest
	return (_Unchecked(
		_STD remove_copy_if(_First, _Last,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION remove
template<class _FwdIt,
class _Ty> inline
	_FwdIt _Remove(_FwdIt _First, _FwdIt _Last, const _Ty& _Val)
{	// remove each matching _Val
	_FwdIt _Next = _First;
	for (++_First; _First != _Last; ++_First)
		if (!(*_First == _Val))
			*_Next++ = _Move(*_First);
	return (_Next);
}

template<class _FwdIt,
class _Ty> inline
	_FwdIt remove(_FwdIt _First, _FwdIt _Last, const _Ty& _Val)
{	// remove each matching _Val
	_First = _STD find(_First, _Last, _Val);
	if (_First == _Last)
		return (_First);	// empty sequence, all done
	else
		return (_Rechecked(_First,
		_Remove(_Unchecked(_First), _Unchecked(_Last), _Val)));
}

// TEMPLATE FUNCTION remove_if
template<class _FwdIt,
class _Pr> inline
	_FwdIt _Remove_if(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// remove each satisfying _Pred
	_FwdIt _Next = _First;
	for (++_First; _First != _Last; ++_First)
		if (!_Pred(*_First))
			*_Next++ = _Move(*_First);
	return (_Next);
}

template<class _FwdIt,
class _Pr> inline
	_FwdIt remove_if(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// remove each satisfying _Pred
	_First = _STD find_if(_First, _Last, _Pred);
	if (_First == _Last)
		return (_First);	// empty sequence, all done
	else
		return (_Rechecked(_First,
		_Remove_if(_Unchecked(_First), _Unchecked(_Last), _Pred)));
}

// TEMPLATE FUNCTION unique WITH PRED
template<class _FwdIt,
class _Pr> inline
	_FwdIt _Unique(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// remove each satisfying _Pred with previous
	if (_First != _Last)
		for (_FwdIt _Firstb; (_Firstb = _First), ++_First != _Last;)
			if (_Pred(*_Firstb, *_First))
			{	// copy down
		for (; ++_First != _Last;)
			if (!_Pred(*_Firstb, *_First))
				*++_Firstb = _Move(*_First);
		return (++_Firstb);
			}
	return (_Last);
}

template<class _FwdIt,
class _Pr> inline
	_FwdIt unique(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// remove each satisfying _Pred with previous
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Unique(_Unchecked(_First), _Unchecked(_Last), _Pred)));
}

// TEMPLATE FUNCTION unique
template<class _FwdIt> inline
_FwdIt unique(_FwdIt _First, _FwdIt _Last)
{	// remove each matching previous
	return (_STD unique(_First, _Last, equal_to<>()));
}

// TEMPLATE FUNCTION unique_copy WITH PRED
template<class _InIt,
class _OutIt,
class _Ty,
class _Pr> inline
	_OutIt _Unique_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, _Ty *)
{	// copy compressing pairs satisfying _Pred, input iterators
	_Ty _Val = *_First;

	for (*_Dest++ = _Val; ++_First != _Last;)
		if (!_Pred(_Val, *_First))
		{	// copy unmatched
		_Val = *_First;
		*_Dest++ = _Val;
		}
	return (_Dest);
}

template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt _Unique_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, input_iterator_tag)
{	// copy compressing pairs satisfying _Pred, input iterators
	return (_Unique_copy(_First, _Last, _Dest, _Pred,
		_Val_type(_First)));
}

template<class _FwdIt,
class _OutIt,
class _Pr> inline
	_OutIt _Unique_copy(_FwdIt _First, _FwdIt _Last,
	_OutIt _Dest, _Pr _Pred, forward_iterator_tag)
{	// copy compressing pairs satisfying _Pred, forward iterators
	_FwdIt _Firstb = _First;

	for (*_Dest++ = *_Firstb; ++_First != _Last;)
		if (!_Pred(*_Firstb, *_First))
		{	// copy unmatched
		_Firstb = _First;
		*_Dest++ = *_Firstb;
		}
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt unique_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred)
{	// copy compressing pairs that match
	return (_First == _Last ? _Dest :
		_Unique_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Pred, _Iter_cat(_First)));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt _Unique_copy1(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, true_type)
{	// copy compressing pairs that match, checked dest
	return (_Unique_copy(_First, _Last,
		_Dest, _Pred, _Iter_cat(_First)));
}

template<class _InIt,
class _OutIt,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Unique_copy1(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred, false_type)
{	// copy compressing pairs that match, unchecked dest
	return (_Unique_copy(_First, _Last,
		_Dest, _Pred, _Iter_cat(_First)));
}

template<class _InIt,
class _OutIt,
class _Pr> inline
	_OutIt unique_copy(_InIt _First, _InIt _Last,
	_OutIt _Dest, _Pr _Pred)
{	// copy compressing pairs that match
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	return (_First == _Last ? _Dest :
		_Unique_copy1(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Pred, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy,
	size_t _OutSize,
class _Pr> inline
	_OutTy *unique_copy(_InIt _First, _InIt _Last,
	_OutTy(&_Dest)[_OutSize], _Pr _Pred)
{	// copy compressing pairs that match, array dest
	return (_Unchecked(
		_STD unique_copy(_First, _Last,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION unique_copy
template<class _InIt,
class _OutIt> inline
	_OutIt unique_copy(_InIt _First, _InIt _Last, _OutIt _Dest)
{	// copy compressing pairs that match
	return (_STD unique_copy(_First, _Last, _Dest,
		equal_to<>()));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt,
class _OutTy,
	size_t _OutSize> inline
	_OutTy *unique_copy(_InIt _First, _InIt _Last,
	_OutTy(&_Dest)[_OutSize])
{	// copy compressing pairs that match, array dest
	return (_STD unique_copy(_First, _Last, _Dest,
		equal_to<>()));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */

// TEMPLATE FUNCTION reverse_copy
template<class _BidIt,
class _OutIt> inline
	_OutIt _Reverse_copy(_BidIt _First, _BidIt _Last,
	_OutIt _Dest)
{	// copy reversing elements in [_First, _Last)
	for (; _First != _Last; ++_Dest)
		*_Dest = *--_Last;
	return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _BidIt,
class _OutIt> inline
	_OutIt reverse_copy(_BidIt _First, _BidIt _Last,
	_OutIt _Dest)
{	// copy reversing elements in [_First, _Last)
	return (_Reverse_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _BidIt,
class _OutIt> inline
	_OutIt _Reverse_copy(_BidIt _First, _BidIt _Last,
	_OutIt _Dest,
	input_iterator_tag, _Mutable_iterator_tag)
{	// copy reversing elements in [_First, _Last), arbitrary iterators
	return (_Reverse_copy(_First, _Last,
		_Dest));
}

template<class _BidIt,
class _OutIt> inline
	_OutIt _Reverse_copy(_BidIt _First, _BidIt _Last,
	_OutIt _Dest,
	random_access_iterator_tag, random_access_iterator_tag)
{	// copy reversing elements in [_First, _Last), random-access iterators
	_OutIt _Ans = _Dest + (_Last - _First);	// also checks range
	_Reverse_copy(_First, _Last,
		_Unchecked(_Dest));
	return (_Ans);
}

template<class _BidIt,
class _OutIt> inline
	_OutIt _Reverse_copy(_BidIt _First, _BidIt _Last,
	_OutIt _Dest,
	true_type)
{	// copy reversing elements in [_First, _Last), checked dest
	return (_Reverse_copy(_First, _Last,
		_Dest, _Iter_cat(_First), _Iter_cat(_Dest)));
}

template<class _BidIt,
class _OutIt> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Reverse_copy(_BidIt _First, _BidIt _Last,
	_OutIt _Dest,
	false_type)
{	// copy reversing elements in [_First, _Last), unchecked dest
	return (_Reverse_copy(_First, _Last,
		_Dest, _Iter_cat(_First), _Iter_cat(_Dest)));
}

template<class _BidIt,
class _OutIt> inline
	_OutIt reverse_copy(_BidIt _First, _BidIt _Last,
	_OutIt _Dest)
{	// copy reversing elements in [_First, _Last)
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	return (_Reverse_copy(_Unchecked(_First), _Unchecked(_Last),
		_Dest, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _BidIt,
class _OutTy,
	size_t _OutSize> inline
	_OutTy *reverse_copy(_BidIt _First, _BidIt _Last,
	_OutTy(&_Dest)[_OutSize])
{	// copy reversing elements in [_First, _Last), array dest
	return (_Unchecked(
		_STD reverse_copy(_First, _Last,
		_Array_iterator<_OutTy, _OutSize>(_Dest))));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION rotate_copy
template<class _FwdIt,
class _OutIt> inline
	_OutIt rotate_copy(_FwdIt _First, _FwdIt _Mid, _FwdIt _Last,
	_OutIt _Dest)
{	// copy rotating [_First, _Last)
	_Dest = _STD copy(_Mid, _Last, _Dest);
	return (_STD copy(_First, _Mid, _Dest));
}

// TEMPLATE FUNCTION random_shuffle WITH RANDOM FN
template<class _RanIt,
class _Fn1,
class _Diff> inline
	void _Random_shuffle(_RanIt _First, _RanIt _Last, _Fn1& _Func, _Diff *)
{	// shuffle nonempty [_First, _Last) using random function _Func
	_RanIt _Next = _First;
	for (_Diff _Index = 2; ++_Next != _Last; ++_Index)
	{	// randomly swap element with self or earlier element
		_Diff _Off = _Func(_Index);

#if _ITERATOR_DEBUG_LEVEL == 2
		if (_Off < 0 || _Index <= _Off)
		{	// report error
			_DEBUG_ERROR("random value out of range");
			_SCL_SECURE_OUT_OF_RANGE;
		}

#elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE_RANGE(0 <= _Off && _Off < _Index);
#endif /* _ITERATOR_DEBUG_LEVEL */

		_STD iter_swap(_Next, _First + _Off);
	}
}

template<class _RanIt,
class _Fn1> inline
	void random_shuffle(_RanIt _First, _RanIt _Last, _Fn1&& _Func)
{	// shuffle [_First, _Last) using random function _Func
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Func);
	if (_First != _Last)
		_Random_shuffle(_Unchecked(_First), _Unchecked(_Last), _Func,
		_Dist_type(_First));
}

// TEMPLATE FUNCTION shuffle WITH URNG
template<class _RanIt,
class _Urng> inline
	void shuffle(_RanIt _First, _RanIt _Last, _Urng&& _Func)
{	// shuffle [_First, _Last) using URNG _Func
	typedef typename iterator_traits<_RanIt>::difference_type _Diff;
	typedef typename remove_reference<_Urng>::type _Urng0;
	_Rng_from_urng<_Diff, _Urng0> _Rng(_Func);
	_STD random_shuffle(_First, _Last, _Rng);
}

// STRUCT _Rand_urng_from_func
struct _Rand_urng_from_func
{	// wrap rand() as a URNG
	typedef unsigned int result_type;

	static result_type(min)()
	{	// return minimum possible generated value
		return (0);
	}

	static result_type(max)()
	{	// return maximum possible generated value
		return (RAND_MAX);
	}

	result_type operator()()
	{	// invoke rand()
		return (_CSTD rand());
	}
};

// TEMPLATE FUNCTION random_shuffle
template<class _RanIt> inline
void random_shuffle(_RanIt _First, _RanIt _Last)
{	// shuffle [_First, _Last) using rand()
	_Rand_urng_from_func _Func;
	_STD shuffle(_First, _Last, _Func);
}

// TEMPLATE FUNCTION partition
template<class _FwdIt,
class _Pr> inline
	_FwdIt _Partition(_FwdIt _First, _FwdIt _Last, _Pr _Pred,
	forward_iterator_tag)
{	// move elements satisfying _Pred to front, forward iterators
	while (_First != _Last && _Pred(*_First))
		++_First;	// skip in-place elements at beginning

	if (_First == _Last)
		return (_First);	// done

	for (_FwdIt _Next = _STD next(_First); _Next != _Last; ++_Next)
		if (_Pred(*_Next))
			_STD iter_swap(_First++, _Next);	// out of place, swap and loop

	return (_First);
}

template<class _BidIt,
class _Pr> inline
	_BidIt _Partition(_BidIt _First, _BidIt _Last, _Pr _Pred,
	bidirectional_iterator_tag)
{	// move elements satisfying _Pred to front, bidirectional iterators
	for (;; ++_First)
	{	// find any out-of-order pair
		for (; _First != _Last && _Pred(*_First); ++_First)
			;	// skip in-place elements at beginning
		if (_First == _Last)
			break;	// done

		for (; _First != --_Last && !_Pred(*_Last);)
			;	// skip in-place elements at end
		if (_First == _Last)
			break;	// done

		_STD iter_swap(_First, _Last);	// out of place, swap and loop
	}
	return (_First);
}

template<class _FwdIt,
class _Pr> inline
	_FwdIt partition(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// move elements satisfying _Pred to beginning of sequence
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Partition(_Unchecked(_First), _Unchecked(_Last), _Pred,
		_Iter_cat(_First))));
}

// TEMPLATE FUNCTION stable_partition
template<class _BidIt,
class _Diff,
class _Ty> inline
	_BidIt _Buffered_rotate(_BidIt _First, _BidIt _Mid, _BidIt _Last,
	_Diff _Count1, _Diff _Count2, _Temp_iterator<_Ty>& _Tempbuf)
{	// rotate [_First, _Last) using temp buffer
	if (_Count1 == 0 || _Count2 == 0)
	{	// do nothing
		_STD advance(_First, _Count2);
		return (_First);
	}
	else if (_Count1 <= _Count2 && _Count1 <= _Tempbuf._Maxlen())
	{	// buffer left partition, then copy parts
		_Move(_First, _Mid, _Tempbuf._Init());
		_Move(_Mid, _Last, _First);
		return (_Move_backward(_Tempbuf._First(), _Tempbuf._Last(),
			_Last));
	}
	else if (_Count2 <= _Tempbuf._Maxlen())
	{	// buffer right partition, then copy parts
		_Move(_Mid, _Last, _Tempbuf._Init());
		_Move_backward(_First, _Mid, _Last);
		return (_Move(_Tempbuf._First(), _Tempbuf._Last(), _First));
	}
	else
	{	// buffer too small, rotate in place
		return (_STD rotate(_First, _Mid, _Last));
	}
}

template<class _BidIt,
class _Pr,
class _Diff,
class _Ty> inline
	_BidIt _Stable_partition(_BidIt _First, _BidIt _Last, _Pr _Pred,
	_Diff _Count, _Temp_iterator<_Ty>& _Tempbuf)
{	// partition preserving order of equivalents, using _Pred
	if (_Count == 0)
		return (_First);
	else if (_Count == 1)
		return (_Pred(*_First) ? _Last : _First);
	else if (_Count <= _Tempbuf._Maxlen())
	{	// temp buffer big enough, copy right partition out and back
		_BidIt _Next = _First;
		for (_Tempbuf._Init(); _First != _Last; ++_First)
			if (_Pred(*_First))
				*_Next++ = _Move(*_First);
			else
				*_Tempbuf++ = _Move(*_First);

		_Move(_Tempbuf._First(), _Tempbuf._Last(), _Next);	// copy back
		return (_Next);
	}
	else
	{	// temp buffer not big enough, divide and conquer
		_BidIt _Mid = _First;
		_STD advance(_Mid, _Count / 2);

		_BidIt _Left = _Stable_partition(_First, _Mid, _Pred,
			_Count / 2, _Tempbuf);	// form L1R1 in left half
		_BidIt _Right = _Stable_partition(_Mid, _Last, _Pred,
			_Count - _Count / 2, _Tempbuf);	// form L2R2 in right half

		_Diff _Count1 = 0;
		_Distance(_Left, _Mid, _Count1);
		_Diff _Count2 = 0;
		_Distance(_Mid, _Right, _Count2);

		return (_Buffered_rotate(_Left, _Mid, _Right,
			_Count1, _Count2, _Tempbuf));	// rotate L1R1L2R2 to L1L2R1R2
	}
}

template<class _BidIt,
class _Pr,
class _Diff,
class _Ty> inline
	_BidIt _Stable_partition(_BidIt _First, _BidIt _Last, _Pr _Pred,
	_Diff *, _Ty *)
{	// partition preserving order of equivalents, using _Pred
	_Diff _Count = 0;
	_Distance(_First, _Last, _Count);
	_Temp_iterator<_Ty> _Tempbuf(_Count);
	return (_Stable_partition(_First, _Last, _Pred, _Count, _Tempbuf));
}

template<class _BidIt,
class _Pr> inline
	_BidIt stable_partition(_BidIt _First, _BidIt _Last, _Pr _Pred)
{	// partition preserving order of equivalents, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_First == _Last ? _First
		: _Rechecked(_First,
		_Stable_partition(_Unchecked(_First), _Unchecked(_Last),
		_Pred, _Dist_type(_First), _Val_type(_First))));
}

#if _ITERATOR_DEBUG_LEVEL == 2
// TEMPLATE FUNCTION _Debug_heap
template<class _RanIt> inline
void _Debug_heap(_RanIt _First, _RanIt _Last)
{	// test if range is a heap ordered by operator<
	if (_First != _Last)
		for (_RanIt _Root = _First; ++_First != _Last; ++_Root)
			if (_DEBUG_LT(*_Root, *_First))
				_DEBUG_ERROR("invalid heap");
			else if (++_First == _Last)
				break;
			else if (_DEBUG_LT(*_Root, *_First))
				_DEBUG_ERROR("invalid heap");
}

// TEMPLATE FUNCTION _Debug_heap WITH PRED
template<class _RanIt,
class _Pr> inline
	void _Debug_heap(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// test if range is a heap ordered by _Pred
	if (_First != _Last)
		for (_RanIt _Root = _First; ++_First != _Last; ++_Root)
			if (_DEBUG_LT_PRED(_Pred, *_Root, *_First))
				_DEBUG_ERROR("invalid heap");
			else if (++_First == _Last)
				break;
			else if (_DEBUG_LT_PRED(_Pred, *_Root, *_First))
				_DEBUG_ERROR("invalid heap");
}

#define _DEBUG_HEAP(first, last)	\
	_Debug_heap(_Unchecked(first), _Unchecked(last))
#define _DEBUG_HEAP_PRED(first, last, pred)	\
	_Debug_heap(_Unchecked(first), _Unchecked(last), pred)

#else /* _ITERATOR_DEBUG_LEVEL == 2 */
#define _DEBUG_HEAP(first, last)
#define _DEBUG_HEAP_PRED(first, last, pred)
#endif /* _ITERATOR_DEBUG_LEVEL == 2 */

// TEMPLATE FUNCTION push_heap WITH PRED
template<class _RanIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Push_heap(_RanIt _First, _Diff _Hole,
	_Diff _Top, _Ty&& _Val, _Pr _Pred)
{	// percolate _Hole to _Top or where _Val belongs, using operator<
	for (_Diff _Idx = (_Hole - 1) / 2;
		_Top < _Hole && _DEBUG_LT_PRED(_Pred, *(_First + _Idx), _Val);
		_Idx = (_Hole - 1) / 2)
	{	// move _Hole up to parent
		*(_First + _Hole) = _Move(*(_First + _Idx));
		_Hole = _Idx;
	}

	*(_First + _Hole) = _Move(_Val);	// drop _Val into final hole
}

template<class _RanIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Push_heap_0(_RanIt _First, _RanIt _Last, _Pr _Pred, _Diff *, _Ty *)
{	// push *_Last onto heap at [_First, _Last), using _Pred
	_Diff _Count = _Last - _First;
	if (0 < _Count)
	{	// worth doing, percolate *_Last
		_Ty _Val = _Move(*_Last);
		_Push_heap(_First, _Count, _Diff(0), _Move(_Val), _Pred);
	}
}

template<class _RanIt,
class _Pr> inline
	void push_heap(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// push *(_Last - 1) onto heap at [_First, _Last - 1), using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	if (_First != _Last)
	{	// check and push to nontrivial heap
		--_Last;
		_DEBUG_HEAP_PRED(_First, _Last, _Pred);
		_Push_heap_0(_Unchecked(_First), _Unchecked(_Last), _Pred,
			_Dist_type(_First), _Val_type(_First));
	}
}

// TEMPLATE FUNCTION push_heap
template<class _RanIt> inline
void push_heap(_RanIt _First, _RanIt _Last)
{	// push *(_Last - 1) onto heap at [_First, _Last - 1), using operator<
	_STD push_heap(_First, _Last, less<>());
}

// TEMPLATE FUNCTION pop_heap WITH PRED
template<class _RanIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Adjust_heap(_RanIt _First, _Diff _Hole, _Diff _Bottom,
	_Ty&& _Val, _Pr _Pred)
{	// percolate _Hole to _Bottom, then push _Val, using _Pred
	_Diff _Top = _Hole;
	_Diff _Idx = 2 * _Hole + 2;

	for (; _Idx < _Bottom; _Idx = 2 * _Idx + 2)
	{	// move _Hole down to larger child
		if (_DEBUG_LT_PRED(_Pred, *(_First + _Idx), *(_First + (_Idx - 1))))
			--_Idx;
		*(_First + _Hole) = _Move(*(_First + _Idx));
		_Hole = _Idx;
	}

	if (_Idx == _Bottom)
	{	// only child at bottom, move _Hole down to it
		*(_First + _Hole) = _Move(*(_First + (_Bottom - 1)));
		_Hole = _Bottom - 1;
	}
	_Push_heap(_First, _Hole, _Top, _Move(_Val), _Pred);
}

template<class _RanIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Pop_heap(_RanIt _First, _RanIt _Last, _RanIt _Dest,
	_Ty&& _Val, _Pr _Pred, _Diff *)
{	// pop *_First to *_Dest and reheap, using _Pred
	*_Dest = _Move(*_First);
	_Adjust_heap(_First, _Diff(0), _Diff(_Last - _First),
		_Move(_Val), _Pred);
}

template<class _RanIt,
class _Ty,
class _Pr> inline
	void _Pop_heap_0(_RanIt _First, _RanIt _Last, _Pr _Pred, _Ty *)
{	// pop *_First to *(_Last - 1) and reheap, using _Pred
	_Ty _Val = _Move(*(_Last - 1));
	_Pop_heap(_First, _Last - 1, _Last - 1,
		_Move(_Val), _Pred, _Dist_type(_First));
}

template<class _RanIt,
class _Pr> inline
	void _Pop_heap(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// pop *_First to *(_Last - 1) and reheap, using _Pred
	_Pop_heap_0(_Unchecked(_First), _Unchecked(_Last), _Pred,
		_Val_type(_First));
}

template<class _RanIt,
class _Pr> inline
	void pop_heap(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// pop *_First to *(_Last - 1) and reheap, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	_DEBUG_HEAP_PRED(_First, _Last, _Pred);
	if (1 < _Last - _First)
		_Pop_heap(_Unchecked(_First), _Unchecked(_Last), _Pred);
}

// TEMPLATE FUNCTION pop_heap
template<class _RanIt> inline
void pop_heap(_RanIt _First, _RanIt _Last)
{	// pop *_First to *(_Last - 1) and reheap, using operator<
	_STD pop_heap(_First, _Last, less<>());
}

// TEMPLATE FUNCTION make_heap WITH PRED
template<class _RanIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Make_heap(_RanIt _First, _RanIt _Last, _Pr _Pred, _Diff *, _Ty *)
{	// make nontrivial [_First, _Last) into a heap, using _Pred
	_Diff _Bottom = _Last - _First;
	for (_Diff _Hole = _Bottom / 2; 0 < _Hole;)
	{	// reheap top half, bottom to top
		--_Hole;
		_Ty _Val = _Move(*(_First + _Hole));
		_Adjust_heap(_First, _Hole, _Bottom,
			_Move(_Val), _Pred);
	}
}

template<class _RanIt,
class _Pr> inline
	void make_heap(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// make [_First, _Last) into a heap, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	if (1 < _Last - _First)
		_Make_heap(_Unchecked(_First), _Unchecked(_Last), _Pred,
		_Dist_type(_First), _Val_type(_First));
}

// TEMPLATE FUNCTION make_heap
template<class _RanIt> inline
void make_heap(_RanIt _First, _RanIt _Last)
{	// make [_First, _Last) into a heap, using operator<
	_STD make_heap(_First, _Last, less<>());
}

// TEMPLATE FUNCTION sort_heap WITH PRED
template<class _RanIt,
class _Pr> inline
	void _Sort_heap(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// order heap by repeatedly popping, using _Pred
	for (; 1 < _Last - _First; --_Last)
		_Pop_heap(_First, _Last, _Pred);
}

template<class _RanIt,
class _Pr> inline
	void sort_heap(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// order heap by repeatedly popping, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	_DEBUG_HEAP_PRED(_First, _Last, _Pred);
	_Sort_heap(_Unchecked(_First), _Unchecked(_Last), _Pred);
}

// TEMPLATE FUNCTION sort_heap
template<class _RanIt> inline
void sort_heap(_RanIt _First, _RanIt _Last)
{	// order heap by repeatedly popping, using operator<
	_STD sort_heap(_First, _Last, less<>());
}

// TEMPLATE FUNCTION lower_bound WITH PRED
template<class _FwdIt,
class _Ty,
class _Diff,
class _Pr> inline
	_FwdIt _Lower_bound(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val, _Pr _Pred, _Diff *)
{	// find first element not before _Val, using _Pred
	_Diff _Count = 0;
	_Distance(_First, _Last, _Count);

	while (0 < _Count)
	{	// divide and conquer, find half that contains answer
		_Diff _Count2 = _Count / 2;
		_FwdIt _Mid = _First;
		_STD advance(_Mid, _Count2);

		if (_Pred(*_Mid, _Val))
			//		if (_DEBUG_LT_PRED(_Pred, *_Mid, _Val))
		{	// try top half
			_First = ++_Mid;
			_Count -= _Count2 + 1;
		}
		else
			_Count = _Count2;
	}
	return (_First);
}

template<class _FwdIt,
class _Ty,
class _Pr> inline
	_FwdIt lower_bound(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val, _Pr _Pred)
{	// find first element not before _Val, using _Pred
	//	_DEBUG_ORDER_PRED(_First, _Last, _Pred);
	return (_Rechecked(_First,
		_Lower_bound(_Unchecked(_First), _Unchecked(_Last), _Val, _Pred,
		_Dist_type(_First))));
}

// TEMPLATE FUNCTION lower_bound
template<class _FwdIt,
class _Ty> inline
	_FwdIt lower_bound(_FwdIt _First, _FwdIt _Last, const _Ty& _Val)
{	// find first element not before _Val, using operator<
	return (_STD lower_bound(_First, _Last, _Val, less<>()));
}

// TEMPLATE FUNCTION upper_bound WITH PRED
template<class _FwdIt,
class _Ty,
class _Diff,
class _Pr> inline
	_FwdIt _Upper_bound(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val, _Pr _Pred, _Diff *)
{	// find first element that _Val is before, using _Pred
	_Diff _Count = 0;
	_Distance(_First, _Last, _Count);

	while (0 < _Count)
	{	// divide and conquer, find half that contains answer
		_Diff _Count2 = _Count / 2;
		_FwdIt _Mid = _First;
		_STD advance(_Mid, _Count2);

		if (!_Pred(_Val, *_Mid))
			//		if (!_DEBUG_LT_PRED(_Pred, _Val, *_Mid))
		{	// try top half
			_First = ++_Mid;
			_Count -= _Count2 + 1;
		}
		else
			_Count = _Count2;
	}
	return (_First);
}

template<class _FwdIt,
class _Ty,
class _Pr> inline
	_FwdIt upper_bound(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val, _Pr _Pred)
{	// find first element that _Val is before, using _Pred
	//	_DEBUG_ORDER_PRED(_First, _Last, _Pred);
	return (_Rechecked(_First,
		_Upper_bound(_Unchecked(_First), _Unchecked(_Last), _Val, _Pred,
		_Dist_type(_First))));
}

// TEMPLATE FUNCTION upper_bound
template<class _FwdIt,
class _Ty> inline
	_FwdIt upper_bound(_FwdIt _First, _FwdIt _Last, const _Ty& _Val)
{	// find first element that _Val is before, using operator<
	return (_STD upper_bound(_First, _Last, _Val, less<>()));
}

// TEMPLATE FUNCTION equal_range WITH PRED
template<class _FwdIt,
class _Ty,
class _Diff,
class _Pr> inline
	pair<_FwdIt, _FwdIt>
	_Equal_range(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val, _Pr _Pred, _Diff *)
{	// find range equivalent to _Val, using _Pred
	_Diff _Count = 0;
	_Distance(_First, _Last, _Count);

	while (0 < _Count)
	{	// divide and conquer, check midpoint
		_Diff _Count2 = _Count / 2;
		_FwdIt _Mid = _First;
		_STD advance(_Mid, _Count2);

		if (_DEBUG_LT_PRED(_Pred, *_Mid, _Val))
		{	// range begins above _Mid, loop
			_First = ++_Mid;
			_Count -= _Count2 + 1;
		}
		else if (_Pred(_Val, *_Mid))
			_Count = _Count2;	// range in first half, loop
		else
		{	// range straddles _Mid, find each end and return
			_FwdIt _First2 = _STD lower_bound(_First, _Mid, _Val, _Pred);
			_STD advance(_First, _Count);
			_FwdIt _Last2 = _STD upper_bound(++_Mid, _First, _Val, _Pred);
			return (pair<_FwdIt, _FwdIt>(_First2, _Last2));
		}
	}

	return (pair<_FwdIt, _FwdIt>(_First, _First));	// empty range
}

template<class _FwdIt,
class _Ty,
class _Pr> inline
	pair<_FwdIt, _FwdIt>
	equal_range(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val, _Pr _Pred)
{	// find range equivalent to _Val, using _Pred
	_DEBUG_ORDER_PRED(_First, _Last, _Pred);
	pair<_UNCHECKED_TYPE(_FwdIt), _UNCHECKED_TYPE(_FwdIt)> _Ans(
		_Equal_range(_Unchecked(_First), _Unchecked(_Last),
		_Val, _Pred, _Dist_type(_First)));
	return (pair<_FwdIt, _FwdIt>(
		_Rechecked(_First, _Ans.first),
		_Rechecked(_Last, _Ans.second)));
}

// TEMPLATE FUNCTION equal_range
template<class _FwdIt,
class _Ty> inline
	pair<_FwdIt, _FwdIt>
	equal_range(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val)
{	// find range equivalent to _Val, using operator<
	return (_STD equal_range(_First, _Last, _Val, less<>()));
}

// TEMPLATE FUNCTION binary_search WITH PRED
template<class _FwdIt,
class _Ty,
class _Pr> inline
	bool binary_search(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val, _Pr _Pred)
{	// test if _Val equivalent to some element, using _Pred
	_First = _STD lower_bound(_First, _Last, _Val, _Pred);
	return (_First != _Last && !_Pred(_Val, *_First));
}

// TEMPLATE FUNCTION binary_search
template<class _FwdIt,
class _Ty> inline
	bool binary_search(_FwdIt _First, _FwdIt _Last, const _Ty& _Val)
{	// test if _Val equivalent to some element, using operator<
	return (_STD binary_search(_First, _Last, _Val, less<>()));
}

// TEMPLATE FUNCTION merge WITH PRED
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Merge0(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// copy merging ranges, both using _Pred
	if (_First1 != _Last1 && _First2 != _Last2)
		for (;;)
		{	// merge either first or second
		if (_DEBUG_LT_PRED(_Pred, *_First2, *_First1))
		{	// merge first
			*_Dest++ = *_First2++;
			if (_First2 == _Last2)
				break;
		}
		else
		{	// merge second
			*_Dest++ = *_First1++;
			if (_First1 == _Last1)
				break;
		}
		}

	_Dest = _Copy_impl(_First1, _Last1, _Dest);	// copy any tail
	return (_Copy_impl(_First2, _Last2, _Dest));
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt merge(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// copy merging ranges, both using _Pred
	return (_Merge0(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Merge2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, input_iterator_tag,
	input_iterator_tag, _Mutable_iterator_tag)
{	// copy merging ranges, both using _Pred, arbitrary iterators
	return (_Merge0(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Merge2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, random_access_iterator_tag,
	random_access_iterator_tag, random_access_iterator_tag)
{	// copy merging ranges, both using _Pred, random-access iterators
	_OutIt _Ans = _Dest + (_Last1 - _First1)
		+ (_Last2 - _First2);	// also checks range
	_Merge0(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred);
	return (_Ans);
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Merge2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, true_type)
{	// copy merging ranges, both using _Pred, checked dest
	return (_Merge2(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred, _Iter_cat(_First1),
		_Iter_cat(_First2), _Iter_cat(_Dest)));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Merge2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, false_type)
{	// copy merging ranges, both using _Pred, unchecked dest
	return (_Merge2(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred, _Iter_cat(_First1),
		_Iter_cat(_First2), _Iter_cat(_Dest)));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt merge(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// copy merging ranges, both using _Pred
	_DEBUG_ORDER_PRED(_First1, _Last1, _Pred);
	_DEBUG_ORDER_PRED(_First2, _Last2, _Pred);
	_DEBUG_POINTER(_Dest);
	_DEBUG_POINTER(_Pred);
	return (_Merge2(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize,
class _Pr> inline
	_OutTy *merge(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutTy(&_Dest)[_OutSize], _Pr _Pred)
{	// copy merging ranges, both using _Pred, array dest
	return (_Unchecked(
		_STD merge(_First1, _Last1,
		_First2, _Last2,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION merge
template<class _InIt1,
class _InIt2,
class _OutIt> inline
	_OutIt merge(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest)
{	// copy merging ranges, both using operator<
	return (_STD merge(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize> inline
	_OutTy *merge(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutTy(&_Dest)[_OutSize])
{	// copy merging ranges, both using operator<, array dest
	return (_STD merge(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */

// TEMPLATE FUNCTION inplace_merge WITH PRED
template<class _BidIt1,
class _BidIt2,
class _BidIt3,
class _Pr> inline
	_BidIt3 _Merge_backward(_BidIt1 _First1, _BidIt1 _Last1,
	_BidIt2 _First2, _BidIt2 _Last2, _BidIt3 _Dest, _Pr _Pred)
{	// merge backwards to _Dest, using _Pred
	if (_First1 != _Last1 && _First2 != _Last2)
		for (;;)
		{	// merge either first or second
		if (_DEBUG_LT_PRED(_Pred, *--_Last2, *--_Last1))
		{	// merge first
			*--_Dest = _Move(*_Last1);
			++_Last2;
			if (_First1 == _Last1)
				break;
		}
		else
		{	// merge second
			*--_Dest = _Move(*_Last2);
			++_Last1;
			if (_First2 == _Last2)
				break;
		}
		}

	_Dest = _Move_backward(_First2, _Last2, _Dest);	// move any tail
	return (_Move_backward(_First1, _Last1, _Dest));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Merge(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// move merging ranges, both using _Pred
	if (_First1 != _Last1 && _First2 != _Last2)
		for (;;)
		{	// merge either first or second
		if (_DEBUG_LT_PRED(_Pred, *_First2, *_First1))
		{	// merge first
			*_Dest++ = _Move(*_First2++);
			if (_First2 == _Last2)
				break;
		}
		else
		{	// merge second
			*_Dest++ = _Move(*_First1++);
			if (_First1 == _Last1)
				break;
		}
		}

	_Dest = _Move(_First1, _Last1, _Dest);	// move any tail
	return (_Move(_First2, _Last2, _Dest));
}

template<class _BidIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Buffered_merge(_BidIt _First, _BidIt _Mid, _BidIt _Last,
	_Diff _Count1, _Diff _Count2,
	_Temp_iterator<_Ty>& _Tempbuf, _Pr _Pred)
{	// merge [_First, _Mid) with [_Mid, _Last), using _Pred
	if (_Count1 == 0 || _Count2 == 0)
		;	// do nothing
	else if (_Count1 + _Count2 == 2)
	{	// order two one-element partitions
		if (_DEBUG_LT_PRED(_Pred, *_Mid, *_First))
			_STD iter_swap(_First, _Mid);
	}
	else if (_Count1 <= _Count2 && _Count1 <= _Tempbuf._Maxlen())
	{	// buffer left partition, then merge
		_Move(_First, _Mid, _Tempbuf._Init());
		_Merge(_Tempbuf._First(), _Tempbuf._Last(),
			_Mid, _Last, _First, _Pred);
	}
	else if (_Count2 <= _Tempbuf._Maxlen())
	{	// buffer right partition, then merge
		_Move(_Mid, _Last, _Tempbuf._Init());
		_Merge_backward(_First, _Mid,
			_Tempbuf._First(), _Tempbuf._Last(), _Last, _Pred);
	}
	else
	{	// buffer too small, divide and conquer
		_BidIt _Firstn, _Lastn;
		_Diff _Count1n, _Count2n;
		if (_Count2 < _Count1)
		{	// left larger, cut it in half and partition right to match
			_Count1n = _Count1 / 2, _Count2n = 0;
			_Firstn = _First;
			_STD advance(_Firstn, _Count1n);
			_Lastn = _STD lower_bound(_Mid, _Last, *_Firstn, _Pred);
			_Distance(_Mid, _Lastn, _Count2n);
		}
		else
		{	// right larger, cut it in half and partition left to match
			_Count1n = 0, _Count2n = _Count2 / 2;
			_Lastn = _Mid;
			_STD advance(_Lastn, _Count2n);
			_Firstn = _STD upper_bound(_First, _Mid, *_Lastn, _Pred);
			_Distance(_First, _Firstn, _Count1n);
		}
		_BidIt _Midn = _Buffered_rotate(_Firstn, _Mid, _Lastn,
			_Count1 - _Count1n, _Count2n, _Tempbuf);	// rearrange middle
		_Buffered_merge(_First, _Firstn, _Midn,
			_Count1n, _Count2n, _Tempbuf, _Pred);	// merge each new part
		_Buffered_merge(_Midn, _Lastn, _Last,
			_Count1 - _Count1n, _Count2 - _Count2n, _Tempbuf, _Pred);
	}
}

template<class _BidIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Inplace_merge(_BidIt _First, _BidIt _Mid, _BidIt _Last, _Pr _Pred,
	_Diff *, _Ty *)
{	// merge [_First, _Mid) with [_Mid, _Last), using _Pred
	_Diff _Count1 = 0;
	_Distance(_First, _Mid, _Count1);
	_Diff _Count2 = 0;
	_Distance(_Mid, _Last, _Count2);
	_Temp_iterator<_Ty> _Tempbuf(_Count1 < _Count2 ? _Count1 : _Count2);
	_Buffered_merge(_First, _Mid, _Last,
		_Count1, _Count2, _Tempbuf, _Pred);
}

template<class _BidIt,
class _Pr> inline
	void inplace_merge(_BidIt _First, _BidIt _Mid, _BidIt _Last, _Pr _Pred)
{	// merge [_First, _Mid) with [_Mid, _Last), using _Pred
	_DEBUG_ORDER_PRED(_First, _Mid, _Pred);
	_DEBUG_ORDER_PRED(_Mid, _Last, _Pred);
	if (_First != _Mid && _Mid != _Last)
		_Inplace_merge(
		_Unchecked(_First), _Unchecked(_Mid), _Unchecked(_Last), _Pred,
		_Dist_type(_First), _Val_type(_First));
}

// TEMPLATE FUNCTION inplace_merge
template<class _BidIt> inline
void inplace_merge(_BidIt _First, _BidIt _Mid, _BidIt _Last)
{	// merge [_First, _Mid) with [_Mid, _Last), using operator<
	_STD inplace_merge(_First, _Mid, _Last, less<>());
}

// TEMPLATE FUNCTION sort WITH PRED
template<class _BidIt,
class _Pr,
class _Ty> inline
	void _Insertion_sort1(_BidIt _First, _BidIt _Last, _Pr _Pred, _Ty *)
{	// insertion sort [_First, _Last), using _Pred
	if (_First != _Last)
		for (_BidIt _Next = _First; ++_Next != _Last;)
		{	// order next element
		_BidIt _Next1 = _Next;
		_Ty _Val = _Move(*_Next);

		if (_DEBUG_LT_PRED(_Pred, _Val, *_First))
		{	// found new earliest element, move to front
			_Move_backward(_First, _Next, ++_Next1);
			*_First = _Move(_Val);
		}
		else
		{	// look for insertion point after first
			for (_BidIt _First1 = _Next1;
				_DEBUG_LT_PRED(_Pred, _Val, *--_First1);
				_Next1 = _First1)
				*_Next1 = _Move(*_First1);	// move hole down
			*_Next1 = _Move(_Val);	// insert element in hole
		}
		}
}

template<class _BidIt,
class _Pr> inline
	void _Insertion_sort(_BidIt _First, _BidIt _Last, _Pr _Pred)
{	// insertion sort [_First, _Last), using _Pred
	_Insertion_sort1(_First, _Last, _Pred, _Val_type(_First));
}

template<class _RanIt,
class _Pr> inline
	void _Med3(_RanIt _First, _RanIt _Mid, _RanIt _Last, _Pr _Pred)
{	// sort median of three elements to middle
	if (_DEBUG_LT_PRED(_Pred, *_Mid, *_First))
		_STD iter_swap(_Mid, _First);
	if (_DEBUG_LT_PRED(_Pred, *_Last, *_Mid))
	{	// swap middle and last, then test first again
		_STD iter_swap(_Last, _Mid);
		if (_DEBUG_LT_PRED(_Pred, *_Mid, *_First))
			_STD iter_swap(_Mid, _First);
	}
}

template<class _RanIt,
class _Pr> inline
	void _Median(_RanIt _First, _RanIt _Mid, _RanIt _Last, _Pr _Pred)
{	// sort median element to middle
	if (40 < _Last - _First)
	{	// median of nine
		size_t _Step = (_Last - _First + 1) / 8;
		_Med3(_First, _First + _Step, _First + 2 * _Step, _Pred);
		_Med3(_Mid - _Step, _Mid, _Mid + _Step, _Pred);
		_Med3(_Last - 2 * _Step, _Last - _Step, _Last, _Pred);
		_Med3(_First + _Step, _Mid, _Last - _Step, _Pred);
	}
	else
		_Med3(_First, _Mid, _Last, _Pred);
}

template<class _RanIt,
class _Pr> inline
	pair<_RanIt, _RanIt>
	_Unguarded_partition(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// partition [_First, _Last), using _Pred
	_RanIt _Mid = _First + (_Last - _First) / 2;
	_Median(_First, _Mid, _Last - 1, _Pred);
	_RanIt _Pfirst = _Mid;
	_RanIt _Plast = _Pfirst + 1;

	while (_First < _Pfirst
		&& !_DEBUG_LT_PRED(_Pred, *(_Pfirst - 1), *_Pfirst)
		&& !_Pred(*_Pfirst, *(_Pfirst - 1)))
		--_Pfirst;
	while (_Plast < _Last
		&& !_DEBUG_LT_PRED(_Pred, *_Plast, *_Pfirst)
		&& !_Pred(*_Pfirst, *_Plast))
		++_Plast;

	_RanIt _Gfirst = _Plast;
	_RanIt _Glast = _Pfirst;

	for (;;)
	{	// partition
		for (; _Gfirst < _Last; ++_Gfirst)
			if (_DEBUG_LT_PRED(_Pred, *_Pfirst, *_Gfirst))
				;
			else if (_Pred(*_Gfirst, *_Pfirst))
				break;
			else if (_Plast++ != _Gfirst)
				_STD iter_swap(_Plast - 1, _Gfirst);
			for (; _First < _Glast; --_Glast)
				if (_DEBUG_LT_PRED(_Pred, *(_Glast - 1), *_Pfirst))
					;
				else if (_Pred(*_Pfirst, *(_Glast - 1)))
					break;
				else if (--_Pfirst != _Glast - 1)
					_STD iter_swap(_Pfirst, _Glast - 1);
				if (_Glast == _First && _Gfirst == _Last)
					return (pair<_RanIt, _RanIt>(_Pfirst, _Plast));

				if (_Glast == _First)
				{	// no room at bottom, rotate pivot upward
					if (_Plast != _Gfirst)
						_STD iter_swap(_Pfirst, _Plast);
					++_Plast;
					_STD iter_swap(_Pfirst++, _Gfirst++);
				}
				else if (_Gfirst == _Last)
				{	// no room at top, rotate pivot downward
					if (--_Glast != --_Pfirst)
						_STD iter_swap(_Glast, _Pfirst);
					_STD iter_swap(_Pfirst, --_Plast);
				}
				else
					_STD iter_swap(_Gfirst++, --_Glast);
	}
}

template<class _RanIt,
class _Diff,
class _Pr> inline
	void _Sort(_RanIt _First, _RanIt _Last, _Diff _Ideal, _Pr _Pred)
{	// order [_First, _Last), using _Pred
	_Diff _Count;
	for (; _ISORT_MAX < (_Count = _Last - _First) && 0 < _Ideal;)
	{	// divide and conquer by quicksort
		pair<_RanIt, _RanIt> _Mid =
			_Unguarded_partition(_First, _Last, _Pred);
		_Ideal /= 2, _Ideal += _Ideal / 2;	// allow 1.5 log2(N) divisions

		if (_Mid.first - _First < _Last - _Mid.second)
		{	// loop on second half
			_Sort(_First, _Mid.first, _Ideal, _Pred);
			_First = _Mid.second;
		}
		else
		{	// loop on first half
			_Sort(_Mid.second, _Last, _Ideal, _Pred);
			_Last = _Mid.first;
		}
	}

	if (_ISORT_MAX < _Count)
	{	// heap sort if too many divisions
		_STD make_heap(_First, _Last, _Pred);
		_STD sort_heap(_First, _Last, _Pred);
	}
	else if (1 < _Count)
		_Insertion_sort(_First, _Last, _Pred);	// small
}

template<class _RanIt,
class _Pr> inline
	void sort(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// order [_First, _Last), using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	_Sort(_Unchecked(_First), _Unchecked(_Last), _Last - _First, _Pred);
}

// TEMPLATE FUNCTION sort
template<class _RanIt> inline
void sort(_RanIt _First, _RanIt _Last)
{	// order [_First, _Last), using operator<
	_STD sort(_First, _Last, less<>());
}

// TEMPLATE FUNCTION stable_sort WITH PRED
template<class _BidIt,
class _OutIt,
class _Diff,
class _Pr> inline
	void _Chunked_merge(_BidIt _First, _BidIt _Last, _OutIt _Dest,
	_Diff _Chunk, _Diff _Count, _Pr _Pred)
{	// copy merging chunks, using _Pred
	for (_Diff _Chunk2 = _Chunk * 2; _Chunk2 <= _Count; _Count -= _Chunk2)
	{	// copy merging pairs of adjacent chunks
		_BidIt _Mid1 = _First;
		_STD advance(_Mid1, _Chunk);
		_BidIt _Mid2 = _Mid1;
		_STD advance(_Mid2, _Chunk);

		_Dest = _Merge(_First, _Mid1, _Mid1, _Mid2, _Dest, _Pred);
		_First = _Mid2;
	}

	if (_Count <= _Chunk)
		_Move(_First, _Last, _Dest);	// copy partial last chunk
	else
	{	// copy merging whole and partial last chunk
		_BidIt _Mid1 = _First;
		_STD advance(_Mid1, _Chunk);

		_Merge(_First, _Mid1, _Mid1, _Last, _Dest, _Pred);
	}
}

template<class _BidIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Buffered_merge_sort(_BidIt _First, _BidIt _Last, _Diff _Count,
	_Temp_iterator<_Ty>& _Tempbuf, _Pr _Pred)
{	// sort using temp buffer for merges, using _Pred
	_BidIt _Mid = _First;
	for (_Diff _Nleft = _Count; _ISORT_MAX <= _Nleft; _Nleft -= _ISORT_MAX)
	{	// sort chunks
		_BidIt _Midn = _Mid;
		_STD advance(_Midn, (int)_ISORT_MAX);

		_Insertion_sort(_Mid, _Midn, _Pred);
		_Mid = _Midn;
	}
	_Insertion_sort(_Mid, _Last, _Pred);	// sort partial last chunk

	for (_Diff _Chunk = _ISORT_MAX; _Chunk < _Count; _Chunk *= 2)
	{	// merge adjacent pairs of chunks to and from temp buffer
		_Chunked_merge(_First, _Last, _Tempbuf._Init(),
			_Chunk, _Count, _Pred);
		_Chunked_merge(_Tempbuf._First(), _Tempbuf._Last(), _First,
			_Chunk *= 2, _Count, _Pred);
	}
}

template<class _BidIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Stable_sort(_BidIt _First, _BidIt _Last, _Diff _Count,
	_Temp_iterator<_Ty>& _Tempbuf, _Pr _Pred)
{	// sort preserving order of equivalents, using _Pred
	if (_Count <= _ISORT_MAX)
		_Insertion_sort(_First, _Last, _Pred);	// small
	else
	{	// sort halves and merge
		_Diff _Count2 = (_Count + 1) / 2;
		_BidIt _Mid = _First;
		_STD advance(_Mid, _Count2);

		if (_Count2 <= _Tempbuf._Maxlen())
		{	// temp buffer big enough, sort each half using buffer
			_Buffered_merge_sort(_First, _Mid, _Count2, _Tempbuf, _Pred);
			_Buffered_merge_sort(_Mid, _Last, _Count - _Count2,
				_Tempbuf, _Pred);
		}
		else
		{	// temp buffer not big enough, divide and conquer
			_Stable_sort(_First, _Mid, _Count2, _Tempbuf, _Pred);
			_Stable_sort(_Mid, _Last, _Count - _Count2, _Tempbuf, _Pred);
		}

		_Buffered_merge(_First, _Mid, _Last,
			_Count2, _Count - _Count2, _Tempbuf, _Pred);	// merge halves
	}
}

template<class _BidIt,
class _Diff,
class _Ty,
class _Pr> inline
	void _Stable_sort(_BidIt _First, _BidIt _Last, _Diff *, _Ty *, _Pr _Pred)
{	// sort preserving order of equivalents, using _Pred
	_Diff _Count = 0;
	_Distance(_First, _Last, _Count);
	_Temp_iterator<_Ty> _Tempbuf((_Count + 1) / 2);
	_Stable_sort(_First, _Last, _Count, _Tempbuf, _Pred);
}

template<class _BidIt,
class _Pr> inline
	void stable_sort(_BidIt _First, _BidIt _Last, _Pr _Pred)
{	// sort preserving order of equivalents, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	if (_First != _Last)
		_Stable_sort(_Unchecked(_First), _Unchecked(_Last),
		_Dist_type(_First), _Val_type(_First), _Pred);
}

// TEMPLATE FUNCTION stable_sort
template<class _BidIt> inline
void stable_sort(_BidIt _First, _BidIt _Last)
{	// sort preserving order of equivalents, using operator<
	_STD stable_sort(_First, _Last, less<>());
}

// TEMPLATE FUNCTION partial_sort WITH PRED
template<class _RanIt,
class _Ty,
class _Pr> inline
	void _Partial_sort(_RanIt _First, _RanIt _Mid, _RanIt _Last,
	_Pr _Pred, _Ty *)
{	// order [_First, _Last) up to _Mid, using _Pred
	_DEBUG_RANGE(_First, _Mid);
	_DEBUG_RANGE(_Mid, _Last);
	_DEBUG_POINTER(_Pred);
	_STD make_heap(_First, _Mid, _Pred);

	for (_RanIt _Next = _Mid; _Next < _Last; ++_Next)
		if (_DEBUG_LT_PRED(_Pred, *_Next, *_First))
		{	// replace top with new largest
		_Ty _Val = _Move(*_Next);
		_Pop_heap(_First, _Mid, _Next, _Move(_Val), _Pred,
			_Dist_type(_First));
		}
	_STD sort_heap(_First, _Mid, _Pred);
}

template<class _RanIt,
class _Pr> inline
	void partial_sort(_RanIt _First, _RanIt _Mid, _RanIt _Last, _Pr _Pred)
{	// order [_First, _Last) up to _Mid, using _Pred
	_Partial_sort(
		_Unchecked(_First), _Unchecked(_Mid), _Unchecked(_Last), _Pred,
		_Val_type(_First));
}

// TEMPLATE FUNCTION partial_sort
template<class _RanIt> inline
void partial_sort(_RanIt _First, _RanIt _Mid, _RanIt _Last)
{	// order [_First, _Last) up to _Mid, using operator<
	_STD partial_sort(_First, _Mid, _Last, less<>());
}

// TEMPLATE FUNCTION partial_sort_copy WITH PRED
template<class _InIt,
class _RanIt,
class _Diff,
class _Ty,
class _Pr> inline
	_RanIt _Partial_sort_copy(_InIt _First1, _InIt _Last1,
	_RanIt _First2, _RanIt _Last2, _Pr _Pred, _Diff *, _Ty *)
{	// copy [_First1, _Last1) into [_First2, _Last2) using _Pred
	_RanIt _Mid2 = _First2;
	for (; _First1 != _Last1 && _Mid2 != _Last2; ++_First1, ++_Mid2)
		*_Mid2 = *_First1;	// copy min(_Last1 - _First1, _Last2 - _First2)
	_STD make_heap(_First2, _Mid2, _Pred);

	for (; _First1 != _Last1; ++_First1)
		if (_DEBUG_LT_PRED(_Pred, *_First1, *_First2))
			_Adjust_heap(_First2, _Diff(0), _Diff(_Mid2 - _First2),
			_Ty(*_First1), _Pred);	// replace top with new largest

	_STD sort_heap(_First2, _Mid2, _Pred);
	return (_Mid2);
}

template<class _InIt,
class _RanIt,
class _Pr> inline
	_RanIt partial_sort_copy(_InIt _First1, _InIt _Last1,
	_RanIt _First2, _RanIt _Last2, _Pr _Pred)
{	// copy [_First1, _Last1) into [_First2, _Last2) using _Pred
	_DEBUG_RANGE(_First1, _Last1);
	_DEBUG_RANGE(_First2, _Last2);
	_DEBUG_POINTER(_Pred);
	return (_First1 == _Last1 || _First2 == _Last2 ? _First2
		: _Rechecked(_First2,
		_Partial_sort_copy(
		_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2), _Pred,
		_Dist_type(_First2), _Val_type(_First1))));
}

// TEMPLATE FUNCTION partial_sort_copy
template<class _InIt,
class _RanIt> inline
	_RanIt partial_sort_copy(_InIt _First1, _InIt _Last1,
	_RanIt _First2, _RanIt _Last2)
{	// copy [_First1, _Last1) into [_First2, _Last2), using operator<
	return (_STD partial_sort_copy(_First1, _Last1, _First2, _Last2,
		less<>()));
}

// TEMPLATE FUNCTION nth_element WITH PRED
template<class _RanIt,
class _Pr> inline
	void _Nth_element(_RanIt _First, _RanIt _Nth, _RanIt _Last, _Pr _Pred)
{	// order Nth element, using _Pred
	for (; _ISORT_MAX < _Last - _First;)
	{	// divide and conquer, ordering partition containing Nth
		pair<_RanIt, _RanIt> _Mid =
			_Unguarded_partition(_First, _Last, _Pred);

		if (_Mid.second <= _Nth)
			_First = _Mid.second;
		else if (_Mid.first <= _Nth)
			return;	// Nth inside fat pivot, done
		else
			_Last = _Mid.first;
	}

	_Insertion_sort(_First, _Last, _Pred);	// sort any remainder
}

template<class _RanIt,
class _Pr> inline
	void nth_element(_RanIt _First, _RanIt _Nth, _RanIt _Last, _Pr _Pred)
{	// order Nth element, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	_Nth_element(
		_Unchecked(_First), _Unchecked(_Nth), _Unchecked(_Last), _Pred);
}

// TEMPLATE FUNCTION nth_element
template<class _RanIt> inline
void nth_element(_RanIt _First, _RanIt _Nth, _RanIt _Last)
{	// order Nth element, using operator<
	_STD nth_element(_First, _Nth, _Last, less<>());
}

// TEMPLATE FUNCTION includes WITH PRED
template<class _InIt1,
class _InIt2,
class _Pr> inline
	bool _Includes(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _Pr _Pred)
{	// test if set [_First1, _Last1) in [_First2, _Last2), using _Pred
	for (; _First1 != _Last1 && _First2 != _Last2;)
		if (_DEBUG_LT_PRED(_Pred, *_First2, *_First1))
			return (false);
		else if (_Pred(*_First1, *_First2))
			++_First1;
		else
		{	// advance both
			++_First1;
			++_First2;
		}
		return (_First2 == _Last2);
}

template<class _InIt1,
class _InIt2,
class _Pr> inline
	bool includes(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _Pr _Pred)
{	// test if set [_First1, _Last1) in [_First2, _Last2), using _Pred
	_DEBUG_ORDER_PRED(_First1, _Last1, _Pred);
	_DEBUG_ORDER_PRED(_First2, _Last2, _Pred);
	return (_Includes(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2), _Pred));
}

// TEMPLATE FUNCTION includes
template<class _InIt1,
class _InIt2> inline
	bool includes(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2)
{	// test if all [_First1, _Last1) in [_First2, _Last2), using operator<
	return (_STD includes(_First1, _Last1, _First2, _Last2,
		less<>()));
}

// TEMPLATE FUNCTION set_union WITH PRED
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Set_union(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest, _Pr _Pred)
{	// OR sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	for (; _First1 != _Last1 && _First2 != _Last2;)
		if (_DEBUG_LT_PRED(_Pred, *_First1, *_First2))
		{	// copy first
		*_Dest++ = *_First1;
		++_First1;
		}
		else if (_Pred(*_First2, *_First1))
		{	// copy second
			*_Dest++ = *_First2;
			++_First2;
		}
		else
		{	// advance both
			*_Dest++ = *_First1;
			++_First1;
			++_First2;
		}
		_Dest = _STD copy(_First1, _Last1, _Dest);
		return (_STD copy(_First2, _Last2, _Dest));
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt set_union(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest, _Pr _Pred)
{	// OR sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	return (_Set_union(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Set_union2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, true_type)
{	// OR sets [_First1, _Last1) and [_First2, _Last2), checked dest
	return (_Set_union(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Set_union2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, false_type)
{	// OR sets [_First1, _Last1) and [_First2, _Last2), unchecked dest
	return (_Set_union(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt set_union(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest, _Pr _Pred)
{	// OR sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	_DEBUG_ORDER_PRED(_First1, _Last1, _Pred);
	_DEBUG_ORDER_PRED(_First2, _Last2, _Pred);
	_DEBUG_POINTER(_Dest);
	return (_Set_union2(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize,
class _Pr> inline
	_OutTy *set_union(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutTy(&_Dest)[_OutSize], _Pr _Pred)
{	// OR sets [_First1, _Last1) and [_First2, _Last2), array dest
	return (_Unchecked(
		set_union(_First1, _Last1,
		_First2, _Last2,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION set_union
template<class _InIt1,
class _InIt2,
class _OutIt> inline
	_OutIt set_union(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest)
{	// OR sets [_First1, _Last1) and [_First2, _Last2), using operator<
	return (_STD set_union(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize> inline
	_OutTy *set_union(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutTy(&_Dest)[_OutSize])
{	// OR sets [_First1, _Last1) and [_First2, _Last2), array dest
	return (_STD set_union(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */

// TEMPLATE FUNCTION set_intersection WITH PRED
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Set_intersection(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest, _Pr _Pred)
{	// AND sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	for (; _First1 != _Last1 && _First2 != _Last2;)
		if (_DEBUG_LT_PRED(_Pred, *_First1, *_First2))
			++_First1;
		else if (_Pred(*_First2, *_First1))
			++_First2;
		else
		{	// copy equivalent
			*_Dest++ = *_First1++;
			++_First2;
		}
		return (_Dest);
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt set_intersection(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest, _Pr _Pred)
{	// AND sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	return (_Set_intersection(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Set_intersection2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, true_type)
{	// AND sets [_First1, _Last1) and [_First2, _Last2), checked dest
	return (_Set_intersection(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Set_intersection2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, false_type)
{	// AND sets [_First1, _Last1) and [_First2, _Last2), unchecked dest
	return (_Set_intersection(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt set_intersection(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest, _Pr _Pred)
{	// AND sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	_DEBUG_ORDER_PRED(_First1, _Last1, _Pred);
	_DEBUG_ORDER_PRED(_First2, _Last2, _Pred);
	_DEBUG_POINTER(_Dest);
	return (_Set_intersection2(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize,
class _Pr> inline
	_OutTy *set_intersection(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutTy(&_Dest)[_OutSize], _Pr _Pred)
{	// AND sets [_First1, _Last1) and [_First2, _Last2), array dest
	return (_Unchecked(
		set_intersection(_First1, _Last1,
		_First2, _Last2,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION set_intersection
template<class _InIt1,
class _InIt2,
class _OutIt> inline
	_OutIt set_intersection(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutIt _Dest)
{	// AND sets [_First1, _Last1) and [_First2, _Last2), using operator<
	return (_STD set_intersection(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize> inline
	_OutTy *set_intersection(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2, _OutTy(&_Dest)[_OutSize])
{	// AND sets [_First1, _Last1) and [_First2, _Last2), array dest
	return (_STD set_intersection(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */

// TEMPLATE FUNCTION set_difference WITH PRED
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Set_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// take set [_First2, _Last2) from [_First1, _Last1), using _Pred
	for (; _First1 != _Last1 && _First2 != _Last2;)
		if (_DEBUG_LT_PRED(_Pred, *_First1, *_First2))
		{	// copy first
		*_Dest++ = *_First1;
		++_First1;
		}
		else if (_Pred(*_First2, *_First1))
			++_First2;
		else
		{	// advance both
			++_First1;
			++_First2;
		}
		return (_STD copy(_First1, _Last1, _Dest));
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt set_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// take set [_First2, _Last2) from [_First1, _Last1), using _Pred
	return (_Set_difference(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Set_difference2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, true_type)
{	// take set [_First1, _Last1) from [_First2, _Last2), checked dest
	return (_Set_difference(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Set_difference2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, false_type)
{	// take set [_First1, _Last1) from [_First2, _Last2), unchecked dest
	return (_Set_difference(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt set_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// take set [_First2, _Last2) from [_First1, _Last1), using _Pred
	_DEBUG_ORDER_PRED(_First1, _Last1, _Pred);
	_DEBUG_ORDER_PRED(_First2, _Last2, _Pred);
	_DEBUG_POINTER(_Dest);
	return (_Set_difference2(_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize,
class _Pr> inline
	_OutTy *set_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutTy(&_Dest)[_OutSize], _Pr _Pred)
{	// take set [_First2, _Last2) from [_First1, _Last1), array dest
	return (_Unchecked(
		set_difference(_First1, _Last1,
		_First2, _Last2,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION set_difference
template<class _InIt1,
class _InIt2,
class _OutIt> inline
	_OutIt set_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest)
{	// take set [_First2, _Last2) from [_First1, _Last1), using operator<
	return (_STD set_difference(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize> inline
	_OutTy *set_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutTy(&_Dest)[_OutSize])
{	// take set [_First2, _Last2) from [_First1, _Last1), array dest
	return (_STD set_difference(_First1, _Last1, _First2, _Last2, _Dest,
		less<>()));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */

// TEMPLATE FUNCTION set_symmetric_difference WITH PRED
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Set_symmetric_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// XOR sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	for (; _First1 != _Last1 && _First2 != _Last2;)
		if (_DEBUG_LT_PRED(_Pred, *_First1, *_First2))
		{	// copy first
		*_Dest++ = *_First1;
		++_First1;
		}
		else if (_Pred(*_First2, *_First1))
		{	// copy second
			*_Dest++ = *_First2;
			++_First2;
		}
		else
		{	// advance both
			++_First1;
			++_First2;
		}
		_Dest = _STD copy(_First1, _Last1, _Dest);
		return (_STD copy(_First2, _Last2, _Dest));
}

#if _ITERATOR_DEBUG_LEVEL == 0
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt set_symmetric_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// XOR sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	return (_Set_symmetric_difference(
		_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred));
}

#else /* _ITERATOR_DEBUG_LEVEL == 0 */
template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt _Set_symmetric_difference2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, true_type)
{	// XOR sets [_First1, _Last1) and [_First2, _Last2), checked dest
	return (_Set_symmetric_difference(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_SCL_INSECURE_DEPRECATE
	_OutIt _Set_symmetric_difference2(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred, false_type)
{	// XOR sets [_First1, _Last1) and [_First2, _Last2), unchecked dest
	return (_Set_symmetric_difference(_First1, _Last1,
		_First2, _Last2,
		_Dest, _Pred));
}

template<class _InIt1,
class _InIt2,
class _OutIt,
class _Pr> inline
	_OutIt set_symmetric_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest, _Pr _Pred)
{	// XOR sets [_First1, _Last1) and [_First2, _Last2), using _Pred
	_DEBUG_ORDER_PRED(_First1, _Last1, _Pred);
	_DEBUG_ORDER_PRED(_First2, _Last2, _Pred);
	_DEBUG_POINTER(_Dest);
	return (_Set_symmetric_difference2(
		_Unchecked(_First1), _Unchecked(_Last1),
		_Unchecked(_First2), _Unchecked(_Last2),
		_Dest, _Pred, _Is_checked(_Dest)));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize,
class _Pr> inline
	_OutTy *set_symmetric_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutTy(&_Dest)[_OutSize], _Pr _Pred)
{	// XOR sets [_First1, _Last1) and [_First2, _Last2), array dest
	return (_Unchecked(
		set_symmetric_difference(_First1, _Last1,
		_First2, _Last2,
		_Array_iterator<_OutTy, _OutSize>(_Dest), _Pred)));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */
#endif /* _ITERATOR_DEBUG_LEVEL == 0 */

// TEMPLATE FUNCTION set_symmetric_difference
template<class _InIt1,
class _InIt2,
class _OutIt> inline
	_OutIt set_symmetric_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutIt _Dest)
{	// XOR sets [_First1, _Last1) and [_First2, _Last2), using operator<
	return (_STD set_symmetric_difference(_First1, _Last1, _First2, _Last2,
		_Dest, less<>()));
}

#if _ITERATOR_DEBUG_ARRAY_OVERLOADS
template<class _InIt1,
class _InIt2,
class _OutTy,
	size_t _OutSize> inline
	_OutTy *set_symmetric_difference(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _InIt2 _Last2,
	_OutTy(&_Dest)[_OutSize])
{	// XOR sets [_First1, _Last1) and [_First2, _Last2), array dest
	return (_STD set_symmetric_difference(_First1, _Last1, _First2, _Last2,
		_Dest, less<>()));
}
#endif /* _ITERATOR_DEBUG_ARRAY_OVERLOADS */

// TEMPLATE FUNCTION max_element WITH PRED
template<class _FwdIt,
class _Pr> inline
	_FwdIt _Max_element(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find largest element, using _Pred
	_FwdIt _Found = _First;
	if (_First != _Last)
		for (; ++_First != _Last;)
			if (_DEBUG_LT_PRED(_Pred, *_Found, *_First))
				_Found = _First;
	return (_Found);
}

template<class _FwdIt,
class _Pr> inline
	_FwdIt max_element(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find largest element, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Max_element(_Unchecked(_First), _Unchecked(_Last), _Pred)));
}

// TEMPLATE FUNCTION max_element
template<class _FwdIt> inline
_FwdIt max_element(_FwdIt _First, _FwdIt _Last)
{	// find largest element, using operator<
	return (_STD max_element(_First, _Last, less<>()));
}

// TEMPLATE FUNCTION min_element WITH PRED
template<class _FwdIt,
class _Pr> inline
	_FwdIt _Min_element(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find smallest element, using _Pred
	_FwdIt _Found = _First;
	if (_First != _Last)
		for (; ++_First != _Last;)
			if (_DEBUG_LT_PRED(_Pred, *_First, *_Found))
				_Found = _First;
	return (_Found);
}

template<class _FwdIt,
class _Pr> inline
	_FwdIt min_element(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find smallest element, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Min_element(_Unchecked(_First), _Unchecked(_Last), _Pred)));
}

// TEMPLATE FUNCTION min_element
template<class _FwdIt> inline
_FwdIt min_element(_FwdIt _First, _FwdIt _Last)
{	// find smallest element, using operator<
	return (_STD min_element(_First, _Last, less<>()));
}

// TEMPLATE FUNCTION minmax_element WITH PRED
template<class _FwdIt,
class _Pr> inline
	pair<_FwdIt, _FwdIt>
	_Minmax_element(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find smallest and largest elements, using _Pred
	pair<_FwdIt, _FwdIt> _Found(_First, _First);

	if (_First != _Last)
		for (; ++_First != _Last;)
		{	// process one or two elements
		_FwdIt _Next = _First;
		if (++_Next == _Last)
		{	// process last element
			if (_DEBUG_LT_PRED(_Pred, *_First, *_Found.first))
				_Found.first = _First;
			else if (!_DEBUG_LT_PRED(_Pred, *_First, *_Found.second))
				_Found.second = _First;
		}
		else
		{	// process next two elements
			if (_DEBUG_LT_PRED(_Pred, *_Next, *_First))
			{	// test _Next for new smallest
				if (_DEBUG_LT_PRED(_Pred, *_Next, *_Found.first))
					_Found.first = _Next;
				if (!_DEBUG_LT_PRED(_Pred, *_First, *_Found.second))
					_Found.second = _First;
			}
			else
			{	// test _First for new smallest
				if (_DEBUG_LT_PRED(_Pred, *_First, *_Found.first))
					_Found.first = _First;
				if (!_DEBUG_LT_PRED(_Pred, *_Next, *_Found.second))
					_Found.second = _Next;
			}
			_First = _Next;
		}
		}
	return (_Found);
}

template<class _FwdIt,
class _Pr> inline
	pair<_FwdIt, _FwdIt>
	minmax_element(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find smallest and largest elements, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	pair<_UNCHECKED_TYPE(_FwdIt), _UNCHECKED_TYPE(_FwdIt)> _Ans(
		_Minmax_element(_Unchecked(_First), _Unchecked(_Last), _Pred));
	return (pair<_FwdIt, _FwdIt>(
		_Rechecked(_First, _Ans.first),
		_Rechecked(_Last, _Ans.second)));
}

// TEMPLATE FUNCTION minmax_element
template<class _FwdIt> inline
pair<_FwdIt, _FwdIt>
minmax_element(_FwdIt _First, _FwdIt _Last)
{	// find smallest and largest elements, using operator<
	return (_STD minmax_element(_First, _Last, less<>()));
}

// TEMPLATE FUNCTION max
template<class _Ty> inline

_Post_equal_to_(_Left < _Right ? _Right : _Left)

const _Ty& (max)(const _Ty& _Left, const _Ty& _Right)
{	// return larger of _Left and _Right
	return (_DEBUG_LT(_Left, _Right) ? _Right : _Left);
}

template<class _Ty> inline
_Ty(max)(_XSTD initializer_list<_Ty> _Ilist)
{	// return leftmost/largest
	const _Ty *_Res = _STD max_element(_Ilist.begin(), _Ilist.end());
	return (*_Res);
}

// TEMPLATE FUNCTION max WITH PRED
template<class _Ty,
class _Pr> inline
	const _Ty& (max)(const _Ty& _Left, const _Ty& _Right, _Pr _Pred)
{	// return larger of _Left and _Right using _Pred
	return (_DEBUG_LT_PRED(_Pred, _Left, _Right) ? _Right : _Left);
}

template<class _Ty,
class _Pr> inline
	_Ty(max)(_XSTD initializer_list<_Ty> _Ilist, _Pr _Pred)
{	// return leftmost/largest
	const _Ty *_Res = _STD max_element(_Ilist.begin(), _Ilist.end(), _Pred);
	return (*_Res);
}

// TEMPLATE FUNCTION min
template<class _Ty> inline

_Post_equal_to_(_Right < _Left ? _Right : _Left)

const _Ty& (min)(const _Ty& _Left, const _Ty& _Right)
{	// return smaller of _Left and _Right
	return (_DEBUG_LT(_Right, _Left) ? _Right : _Left);
}

template<class _Ty> inline
_Ty(min)(_XSTD initializer_list<_Ty> _Ilist)
{	// return leftmost/smallest
	const _Ty *_Res = _STD min_element(_Ilist.begin(), _Ilist.end());
	return (*_Res);
}

// TEMPLATE FUNCTION min WITH PRED
template<class _Ty,
class _Pr> inline
	const _Ty& (min)(const _Ty& _Left, const _Ty& _Right, _Pr _Pred)
{	// return smaller of _Left and _Right using _Pred
	return (_DEBUG_LT_PRED(_Pred, _Right, _Left) ? _Right : _Left);
}

template<class _Ty,
class _Pr> inline
	_Ty(min)(_XSTD initializer_list<_Ty> _Ilist, _Pr _Pred)
{	// return leftmost/smallest
	const _Ty *_Res = _STD min_element(_Ilist.begin(), _Ilist.end(), _Pred);
	return (*_Res);
}

// TEMPLATE FUNCTION minmax
template<class _Ty> inline
pair<const _Ty&, const _Ty&>
minmax(const _Ty& _Left, const _Ty& _Right)
{	// return pair(leftmost/smaller, rightmost/larger) of _Left and _Right
	return (_Right < _Left
		? pair<const _Ty&, const _Ty&>(_Right, _Left)
		: pair<const _Ty&, const _Ty&>(_Left, _Right));
}

template<class _Ty> inline
pair<_Ty, _Ty> minmax(_XSTD initializer_list<_Ty> _Ilist)
{	// return {leftmost/smallest, rightmost/largest}
	pair<const _Ty *, const _Ty *> _Res = _STD minmax_element(
		_Ilist.begin(), _Ilist.end());
	return (pair<_Ty, _Ty>(*_Res.first, *_Res.second));
}

// TEMPLATE FUNCTION minmax WITH PRED
template<class _Ty,
class _Pr> inline
	pair<const _Ty&, const _Ty&>
	minmax(const _Ty& _Left, const _Ty& _Right, _Pr _Pred)
{	// return pair(leftmost/smaller, rightmost/larger) of _Left and _Right
	return (_Pred(_Right, _Left)
		? pair<const _Ty&, const _Ty&>(_Right, _Left)
		: pair<const _Ty&, const _Ty&>(_Left, _Right));
}

template<class _Ty,
class _Pr> inline
	pair<_Ty, _Ty> minmax(_XSTD initializer_list<_Ty> _Ilist, _Pr _Pred)
{	// return {leftmost/smallest, rightmost/largest}
	pair<const _Ty *, const _Ty *> _Res = _STD minmax_element(
		_Ilist.begin(), _Ilist.end(), _Pred);
	return (pair<_Ty, _Ty>(*_Res.first, *_Res.second));
}

// TEMPLATE FUNCTION next_permutation WITH PRED
template<class _BidIt,
class _Pr> inline
	bool _Next_permutation(_BidIt _First, _BidIt _Last, _Pr _Pred)
{	// permute and test for pure ascending, using _Pred
	_BidIt _Next = _Last;
	if (_First == _Last || _First == --_Next)
		return (false);

	for (;;)
	{	// find rightmost element smaller than successor
		_BidIt _Next1 = _Next;
		if (_DEBUG_LT_PRED(_Pred, *--_Next, *_Next1))
		{	// swap with rightmost element that's smaller, flip suffix
			_BidIt _Mid = _Last;
			for (; !_DEBUG_LT_PRED(_Pred, *_Next, *--_Mid);)
				;
			_STD iter_swap(_Next, _Mid);
			_STD reverse(_Next1, _Last);
			return (true);
		}

		if (_Next == _First)
		{	// pure descending, flip all
			_STD reverse(_First, _Last);
			return (false);
		}
	}
}

template<class _BidIt,
class _Pr> inline
	bool next_permutation(_BidIt _First, _BidIt _Last, _Pr _Pred)
{	// permute and test for pure ascending, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Next_permutation(_Unchecked(_First), _Unchecked(_Last), _Pred));
}

// TEMPLATE FUNCTION next_permutation
template<class _BidIt> inline
bool next_permutation(_BidIt _First, _BidIt _Last)
{	// permute and test for pure ascending, using operator<
	return (_STD next_permutation(_First, _Last, less<>()));
}

// TEMPLATE FUNCTION prev_permutation WITH PRED
template<class _BidIt,
class _Pr> inline
	bool _Prev_permutation(_BidIt _First, _BidIt _Last, _Pr _Pred)
{	// reverse permute and test for pure descending, using _Pred
	_BidIt _Next = _Last;
	if (_First == _Last || _First == --_Next)
		return (false);

	for (;;)
	{	// find rightmost element not smaller than successor
		_BidIt _Next1 = _Next;
		if (_DEBUG_LT_PRED(_Pred, *_Next1, *--_Next))
		{	// swap with rightmost element that's not smaller, flip suffix
			_BidIt _Mid = _Last;
			for (; !_DEBUG_LT_PRED(_Pred, *--_Mid, *_Next);)
				;
			_STD iter_swap(_Next, _Mid);
			_STD reverse(_Next1, _Last);
			return (true);
		}

		if (_Next == _First)
		{	// pure ascending, flip all
			_STD reverse(_First, _Last);
			return (false);
		}
	}
}

template<class _BidIt,
class _Pr> inline
	bool prev_permutation(_BidIt _First, _BidIt _Last, _Pr _Pred)
{	// reverse permute and test for pure descending, using _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Prev_permutation(_Unchecked(_First), _Unchecked(_Last), _Pred));
}

// TEMPLATE FUNCTION prev_permutation
template<class _BidIt> inline
bool prev_permutation(_BidIt _First, _BidIt _Last)
{	// reverse permute and test for pure descending, using operator<
	return (_STD prev_permutation(_First, _Last, less<>()));
}

// TEMPLATE FUNCTIONS is_heap AND is_heap_until WITH PRED
template<class _RanIt,
class _Diff,
class _Pr> inline
	_RanIt _Is_heap_until(_RanIt _First, _RanIt _Last, _Pr _Pred, _Diff *)
{	// find extent of range that is a heap ordered by _Pred
	_Diff _Size = _Last - _First;

	if (2 <= _Size)
		for (_Diff _Off = 0; ++_Off < _Size;)
			if (_DEBUG_LT_PRED(_Pred, *(_First + (_Off - 1) / 2),
				*(_First + _Off)))
				return (_First + _Off);
	return (_Last);
}

template<class _RanIt,
class _Pr>
	_RanIt is_heap_until(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// find extent of range that is a heap ordered by _Pred
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Is_heap_until(_Unchecked(_First), _Unchecked(_Last), _Pred,
		_Dist_type(_First))));
}

template<class _RanIt,
class _Pr>
	bool is_heap(_RanIt _First, _RanIt _Last, _Pr _Pred)
{	// test if range is a heap ordered by _Pred
	return (_Is_heap_until(_First, _Last, _Pred, _Dist_type(_First))
		== _Last);
}

// TEMPLATE FUNCTIONS is_heap AND is_heap_until
template<class _RanIt>
_RanIt is_heap_until(_RanIt _First, _RanIt _Last)
{	// find extent of range that is a heap ordered by operator<
	return (_STD is_heap_until(_First, _Last, less<>()));
}

template<class _RanIt>
bool is_heap(_RanIt _First, _RanIt _Last)
{	// test if range is a heap ordered by operator<
	return (_STD is_heap(_First, _Last, less<>()));
}

// TEMPLATE FUNCTIONS is_sorted AND is_sorted_until WITH PRED
template<class _FwdIt,
class _Pr> inline
	_FwdIt _Is_sorted_until(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find extent of range that is ordered by predicate
	if (_First != _Last)
		for (_FwdIt _Next = _First; ++_Next != _Last; ++_First)
			if (_DEBUG_LT_PRED(_Pred, *_Next, *_First))
				return (_Next);
	return (_Last);
}

template<class _FwdIt,
class _Pr> inline
	_FwdIt is_sorted_until(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// find extent of range that is ordered by predicate
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Pred);
	return (_Rechecked(_First,
		_Is_sorted_until(_Unchecked(_First), _Unchecked(_Last), _Pred)));
}

template<class _FwdIt,
class _Pr> inline
	bool is_sorted(_FwdIt _First, _FwdIt _Last, _Pr _Pred)
{	// test if range is ordered by predicate
	return (_STD is_sorted_until(_First, _Last, _Pred) == _Last);
}

// TEMPLATE FUNCTIONS is_sorted AND is_sorted_until
template<class _FwdIt> inline
_FwdIt is_sorted_until(_FwdIt _First, _FwdIt _Last)
{	// find extent of range that is ordered by operator<
	return (_STD is_sorted_until(_First, _Last, less<>()));
}

template<class _FwdIt> inline
bool is_sorted(_FwdIt _First, _FwdIt _Last)
{	// test if range is ordered by operator<
	return (_STD is_sorted(_First, _Last, less<>()));
}
_STD_END
#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _ALGORITHM_ */

/*
* This file is derived from software bearing the following
* restrictions:
*
* Copyright (c) 1994
* Hewlett-Packard Company
*
* Permission to use, copy, modify, distribute and sell this
* software and its documentation for any purpose is hereby
* granted without fee, provided that the above copyright notice
* appear in all copies and that both that copyright notice and
* this permission notice appear in supporting documentation.
* Hewlett-Packard Company makes no representations about the
* suitability of this software for any purpose. It is provided
* "as is" without express or implied warranty.
*/

/*
* Copyright (c) 1992-2012 by P.J. Plauger.  ALL RIGHTS RESERVED.
* Consult your license regarding permissions and restrictions.
V6.00:0009 */