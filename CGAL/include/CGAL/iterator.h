// Copyright (c) 2003  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/trunk/STL_Extension/include/CGAL/iterator.h $
// $Id: iterator.h 56904 2010-06-21 09:48:18Z sloriot $
// 
//
// Author(s)     : Michael Hoffmann <hoffmann@inf.ethz.ch>
//                 Lutz Kettner <kettner@mpi-sb.mpg.de>
//                 Sylvain Pion

#ifndef CGAL_ITERATOR_H
#define CGAL_ITERATOR_H 1

#include <CGAL/circulator.h>
#include <vector>
#include <map>
#include <boost/type_traits.hpp>
#include <CGAL/tuple.h>

#if defined(BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable:4396)
#endif
namespace CGAL {

// +----------------------------------------------------------------+
// | Emptyset_iterator
// +----------------------------------------------------------------+
// |  sends everything to /dev/null
// +----------------------------------------------------------------+

struct Emptyset_iterator
  : public std::iterator< std::output_iterator_tag, void, void, void, void >
{
  template< class T >
  Emptyset_iterator& operator=(const T&) { return *this; }

  Emptyset_iterator& operator++()        { return *this; }
  Emptyset_iterator& operator++(int)     { return *this; }

  Emptyset_iterator& operator*()         { return *this; }
};

// +---------------------------------------------------------------------+
// | Insert_iterator
// +---------------------------------------------------------------------+
// | Insert output iterator, which calls insert(value) on the container.
// | Similar to std::insert_iterator<> except it doesn't pass an iterator.
// +---------------------------------------------------------------------+

template < class Container >
class Insert_iterator
  : public std::iterator< std::output_iterator_tag, void, void, void, void >
{
protected:
  Container *container;
public:
  typedef Container container_type;

  explicit Insert_iterator(Container &c)
  : container(&c) {}

  Insert_iterator&
  operator=(typename Container::const_reference value)
  {
    container->insert(value);
    return *this;
  }

  Insert_iterator&
  operator*() { return *this; }

  Insert_iterator&
  operator++() { return *this; }

  Insert_iterator
  operator++(int) { return *this; }
};

template < class Container >
inline Insert_iterator<Container>
inserter(Container &x)
{ return Insert_iterator<Container>(x); }

// +----------------------------------------------------------------+
// | Oneset_iterator
// +----------------------------------------------------------------+
// |  stores a pointer to an object of type T
// |  which will be affected by operator*().
// +----------------------------------------------------------------+

template < class T >
class Oneset_iterator
  : public std::iterator< std::bidirectional_iterator_tag,
			  void, void, void, void >
{
  T* t;
  
public:
  // types
  typedef Oneset_iterator<T> Self;
  
public:
  Oneset_iterator(T& t) : t(&t) {}

  T&       operator*()        { return *t; }
  const T& operator*()  const { return *t; }
  T*       operator->()       { return t; }
  const T* operator->() const { return t; }

  Self&    operator++()       { return *this; }
  Self&    operator++(int)    { return *this; }

  Self&    operator--()       { return *this; }
  Self&    operator--(int)    { return *this; }
};

// +----------------------------------------------------------------+
// | Const_oneset_iterator
// +----------------------------------------------------------------+
// |  stores an object of type T
// |  which will be affected by operator*().
// +----------------------------------------------------------------+

template < typename T >
class Const_oneset_iterator {
public:
  
  // types
  typedef  std::random_access_iterator_tag    iterator_category;
  typedef  std::ptrdiff_t                     difference_type;
  typedef  T                                  value_type;
  typedef  value_type*                        pointer;
  typedef  value_type&                        reference;
  
  typedef  Const_oneset_iterator<T>           Self;
  typedef  difference_type                    Diff;
  typedef  value_type                         Val;
  typedef  pointer                            Ptr;
  typedef  reference                          Ref;
  
  // construction
  Const_oneset_iterator( const T& t = T(), Diff n = 0)
    : value( t), index( n)
  { }
  
  // access
  Ref               operator *  ( )       { return  value; }
  const value_type& operator *  ( ) const { return  value; }
  Ptr               operator -> ( )       { return &value; }
  const value_type* operator -> ( ) const { return &value; }
  
  // equality operator
  bool       operator == ( const Self& x) const { return ( index==x.index); }
  bool       operator != ( const Self& x) const { return ( index!=x.index); }
  
  // forward operations
  // ------------------
  Self&      operator ++ (    ) {                   ++index; return *this; }
  Self       operator ++ ( int) { Self tmp = *this; ++index; return tmp;   }
  
  // bidirectional operations
  // ------------------------
  Self&      operator -- (    ) {                   --index; return *this; }
  Self       operator -- ( int) { Self tmp = *this; --index; return tmp;   }
  
  // random access operations
  // ------------------------
  // access
  Ref               operator [] ( Diff )       { return value;}
  const value_type& operator [] ( Diff ) const { return value;}
  
  // less operator
  bool       operator <  ( const Self& x) const { return ( index < x.index);}
  
  // arithmetic operations
  Self&      operator += ( Diff n) { index += n; return *this; }
  Self&      operator -= ( Diff n) { index -= n; return *this; }
  
  Self       operator +  ( Diff n) const { Self tmp = *this; return tmp+=n; }
  Self       operator -  ( Diff n) const { Self tmp = *this; return tmp-=n; }
  
  Diff       operator -  ( const Self& x) const { return index - x.index; }
  
private:
  
  // data members
  Val   value;
  Diff  index;
};

// +----------------------------------------------------------------+
// | Counting_output_iterator
// +----------------------------------------------------------------+
// |  stores a pointer to an int,
// |  which will be incremented by operator=().
// +----------------------------------------------------------------+

// Undocumented, because there is some hope to merge it into Counting_iterator
class Counting_output_iterator
  : public std::iterator< std::output_iterator_tag, void, void, void, void >
{
  std::size_t *c;
public:
  Counting_output_iterator(std::size_t *cc) : c(cc) { *c = 0; }

  Counting_output_iterator& operator++()    { return *this; }
  Counting_output_iterator& operator++(int) { return *this; }

  Counting_output_iterator& operator*() { return *this; }

  template <typename T>
  void operator=(const T&) { ++*c; }

  std::size_t current_counter() const { return *c; }
};

template < class I,
           class Val = typename std::iterator_traits<I>::value_type >
class Counting_iterator {
protected:
  I            nt;    // The internal iterator.
  std::size_t  d_i;   // The internal counter.
public:
  typedef I  Iterator;
  typedef Counting_iterator<I,Val> Self;

  typedef std::input_iterator_tag  iterator_category;
  typedef Val                      value_type;
  typedef std::ptrdiff_t           difference_type;
  typedef const value_type&        reference;
  typedef const value_type*        pointer;

  // CREATION
  // --------

  Counting_iterator( std::size_t i = 0)             : d_i(i) {}
  Counting_iterator( Iterator j, std::size_t i = 0) : nt(j), d_i(i) {}

  // OPERATIONS Forward Category
  // ---------------------------

  Iterator    current_iterator() const { return nt;}
  std::size_t current_counter()  const { return d_i;}

  bool operator==( const Self& i) const { return ( d_i == i.d_i); }
  bool operator!=( const Self& i) const { return !(*this == i);   }
  reference  operator*()  const { return *nt; }
  pointer    operator->() const { return nt.operator->(); }
  Self& operator++() {
    ++nt;
    ++d_i;
    return *this;
  }
  Self  operator++(int) {
    Self tmp = *this;
    ++*this;
    return tmp;
  }
};

template < class I, int N,
           class Ref  = typename std::iterator_traits<I>::reference,
           class Ptr  = typename std::iterator_traits<I>::pointer,
           class Val  = typename std::iterator_traits<I>::value_type,
           class Dist = typename std::iterator_traits<I>::difference_type,
           class Ctg  = typename std::iterator_traits<I>::iterator_category >
class N_step_adaptor {
protected:
  I        nt;    // The internal iterator.
  bool     empty;
public:
  typedef I                                        Iterator;
  typedef N_step_adaptor<I,N>                      Self;
  typedef std::iterator_traits<I>          ITI;
  typedef typename ITI::reference          reference;
  typedef typename ITI::pointer            pointer;
  typedef typename ITI::value_type         value_type;
  typedef typename ITI::difference_type    difference_type;
  typedef typename ITI::iterator_category  iterator_category;
  // Special for circulators.
  typedef I_Circulator_size_traits<iterator_category,I> C_S_Traits;
  typedef typename  C_S_Traits::size_type               size_type;

  // CREATION
  // --------

  N_step_adaptor(): empty(true) {}
  N_step_adaptor( Iterator j) : nt(j), empty(false) {}

  template <class II>
  N_step_adaptor( const N_step_adaptor<II,N>& j)
    : nt( j.current_iterator()), empty(j.empty) {}

  // OPERATIONS Forward Category
  // ---------------------------

  // Circulator stuff.
  typedef  I  Circulator;
  Circulator  current_circulator() const { return nt;}

  Iterator  current_iterator() const { return nt;}
  bool operator==( Nullptr_t p) const {
    CGAL_assertion( p == 0);
    return empty;
  }
  bool  operator!=( Nullptr_t p) const { return !(*this == p); }
  bool  operator==( const Self& i) const { return (empty && i.empty) ||( nt == i.nt); }
  bool  operator!=( const Self& i) const { return !(*this == i); }
  reference operator*()  const { return *nt; }
  pointer   operator->() const { return nt.operator->(); }
  Self& operator++() {
    std::advance( nt, N);
    return *this;
  }
  Self  operator++(int) {
    Self tmp = *this;
    ++*this;
    return tmp;
  }

  // OPERATIONS Bidirectional Category
  // ---------------------------------

  Self& operator--() {
    std::advance( nt, -N);
    return *this;
  }
  Self  operator--(int) {
    Self tmp = *this;
    --*this;
    return tmp;
  }

  // OPERATIONS Random Access Category
  // ---------------------------------

  Self  min_circulator() const { return Self( nt.min_circulator()); }
  Self& operator+=( difference_type n) {
    nt += difference_type(N * n);
    return *this;
  }
  Self  operator+( difference_type n) const {
    Self tmp = *this;
    tmp.nt += difference_type(N * n);
    return tmp;
  }
  Self& operator-=( difference_type n) {
    return operator+=( -n);
  }
  Self  operator-( difference_type n) const {
    Self tmp = *this;
    return tmp += -n;
  }
  difference_type  operator-( const Self& i) const { return (nt-i.nt)/N;}
  reference operator[]( difference_type n) const {
    Self tmp = *this;
    tmp += n;
    return tmp.operator*();
  }
  bool operator<( const Self& i) const { return ( nt < i.nt); }
  bool operator>( const Self& i) const { return i < *this; }
  bool operator<=( const Self& i) const { return !(i < *this); }
  bool operator>=( const Self& i) const { return !(*this < i); }
};

// Microsoft 1300 cannot handle the default template parameters. Hence, ...
template < class I, int N, class Ref, class Ptr, 
	   class Val, class Dist, class Ctg >
inline
N_step_adaptor<I,N,Ref,Ptr,Val,Dist,Ctg>
operator+(typename N_step_adaptor<I,N,Ref,Ptr,Val,Dist,Ctg>::difference_type n,
	  N_step_adaptor<I,N,Ref,Ptr,Val,Dist,Ctg> i)
{ return i += n; }

template < class I, int N>
class N_step_adaptor_derived : public I {
public:
    typedef I                               Iterator;
    typedef I                               Circulator;
    typedef N_step_adaptor_derived<I,N>     Self;
    typedef typename I::iterator_category   iterator_category;
    typedef typename I::value_type          value_type;
    typedef typename I::difference_type     difference_type;
    typedef typename I::reference           reference;
    typedef typename I::pointer             pointer;
    // Special for circulators.
    typedef I_Circulator_size_traits<iterator_category,I> C_S_Traits;
    typedef typename  C_S_Traits::size_type               size_type;

// CREATION
// --------

    N_step_adaptor_derived() {}
    N_step_adaptor_derived( Iterator j) : I(j) {}

    template <class II>
    N_step_adaptor_derived( const N_step_adaptor_derived<II,N>& j)
        : I( j.current_iterator()) {}

// OPERATIONS Forward Category
// ---------------------------

    Circulator current_circulator() const { return *this;}
    Iterator   current_iterator()   const { return *this;}

    Self& operator++() {
        std::advance( (I&)*this, N);
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }

// OPERATIONS Bidirectional Category
// ---------------------------------

    Self& operator--() {
        std::advance( (I&)*this, -N);
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }

// OPERATIONS Random Access Category
// ---------------------------------

    Self  min_circulator() const { return Self( I::min_circulator()); }
    Self& operator+=( difference_type n) {
        I::operator+=( difference_type(N * n));
        return *this;
    }
    Self  operator+( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp;
    }
    Self& operator-=( difference_type n) {
        return operator+=( -n);
    }
    Self  operator-( difference_type n) const {
        Self tmp = *this;
        return tmp += -n;
    }
    difference_type  operator-( const Self& i) const {
        return (I::operator-(i)) / N;
    }
    reference  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
};

template < class I, int N >
inline
N_step_adaptor_derived<I,N>
operator+( typename N_step_adaptor_derived<I,N>::difference_type n,
           N_step_adaptor_derived<I,N> i)
{ return i += n; }

template < class I, class P > struct Filter_iterator;

template < class I, class P >
bool operator==(const Filter_iterator<I,P>&, const Filter_iterator<I,P>&);

template < class I, class P >
struct Filter_iterator {
  typedef I                                Iterator;
  typedef P                                Predicate;
  typedef Filter_iterator<I,P>             Self;
  typedef std::iterator_traits<I>          ITI;
  typedef typename ITI::reference          reference;
  typedef typename ITI::pointer            pointer;
  typedef typename ITI::value_type         value_type;
  typedef typename ITI::difference_type    difference_type;
  typedef typename ITI::iterator_category  iterator_category;
  // Special for circulators.
  typedef I_Circulator_size_traits<iterator_category,I> C_S_Traits;
  typedef typename  C_S_Traits::size_type               size_type;

protected:
  Iterator e_;       // past-the-end position.
  Iterator c_;       // current position.
  Predicate p_;      // Leave out x <==> p_(x).
public:

  Filter_iterator() {}

  Filter_iterator(Iterator e, const Predicate& p)
  : e_(e), c_(e), p_(p) {}

  Filter_iterator(Iterator e, const Predicate& p, Iterator c)
  : e_(e), c_(c), p_(p)
  {
    while (c_ != e_ && p_(c_))
      ++c_;
  }

  Self& operator++() {
    do { ++c_; } while (c_ != e_ && p_(c_));
    return *this;
  }

  Self& operator--() {
    do {
      --c_;
    } while (p_(c_));
    return *this;
  }

  Self operator++(int) {
    Self tmp(*this);
    ++(*this);
    return tmp;
  }

  Self operator--(int) {
    Self tmp(*this);
    --(*this);
    return tmp;
  }

  reference operator*() const { return *c_;  }
  pointer operator->() const  { return &*c_; }
  const Predicate& predicate() const { return p_; }
  Iterator base() const { return c_; }

  bool is_end() const { return (c_ == e_); }

  friend bool operator== <>(const Self&, const Self&);
};

template < class I, class P >
inline Filter_iterator< I, P >
filter_iterator(I e, const P& p)
{ return Filter_iterator< I, P >(e, p); }

template < class I, class P >
inline Filter_iterator< I, P >
filter_iterator(I e, const P& p, I c)
{ return Filter_iterator< I, P >(e, p, c); }

template < class I, class P >
inline
bool operator==(const Filter_iterator<I,P>& it1,
                const Filter_iterator<I,P>& it2)
{
  CGAL_precondition(it1.e_ == it2.e_);
  return it1.base() == it2.base();
}

template < class I, class P >
inline
bool operator!=(const Filter_iterator<I,P>& it1,
                const Filter_iterator<I,P>& it2)
{ return !(it1 == it2); }

template <class I1,class Op>
class Join_input_iterator_1 : public 
std::iterator<typename std::iterator_traits<I1>::iterator_category, 
	      typename Op::result_type, 
	      typename std::iterator_traits<I1>::difference_type, 
	      typename Op::result_type*,
	      typename Op::result_type&>
{ 
public: 
  typedef Join_input_iterator_1<I1,Op> Self;
  typedef typename Op::result_type value_type;
  typedef typename std::iterator_traits<I1>::difference_type difference_type; 
  typedef value_type* pointer;
  typedef value_type& reference; 
  
protected:
  I1 i1;
  Op op;
  mutable value_type val;  // Note: mutable is needed because we want to
                           // return a reference in operator*() and
                           // operator[](int) below.

public:
  Join_input_iterator_1() {}
  Join_input_iterator_1(const Join_input_iterator_1& it)
    : i1(it.i1), op(it.op) {}
  Join_input_iterator_1(I1 i,const Op& o=Op())
    : i1(i), op(o) {}
  
  I1 current_iterator1() const { return i1; }
  
  bool operator==(const Self& i) const {
    return i1 == i.i1;
  }
  bool operator!=(const Self& i) const { return !(*this == i); }
  bool operator< (const Self& i) const {
    return i1 < i.i1;
  }

  Join_input_iterator_1& operator=(const Join_input_iterator_1& it)
  {
    i1 = it.i1;
    op = it.op;
    return *this;
  }
  
  const value_type& operator*() const { 
    val = op(*i1);
    return val;
  }
  
  Self& operator++(   ) {
    ++i1;
    return *this;
  }
  Self  operator++(int) { Self tmp = *this; ++(*this); return tmp; }
  Self& operator--(   ) {
    --i1;
    return *this;
  }
  Self  operator--(int) { Self tmp = *this; --(*this); return tmp; }
  
  const value_type& operator[](difference_type i) const {
    val = op(i1[i]);
    return val;
  }
  
  Self& operator+=(difference_type n) {
    i1 += n;
    return *this;
  }
  Self& operator-=(difference_type n) {
    i1 -= n;
    return *this;
  }
  Self  operator+ (difference_type n) const {
    Self tmp = *this;
    return tmp += n;
  }
  Self  operator- (difference_type n) const {
    Self tmp = *this;
    return tmp -= n;
  }
  difference_type operator-(const Self& i) const { return i1 - i.i1; }
};

template <class I1,class I2,class Op>
class Join_input_iterator_2 : public 
std::iterator<typename std::iterator_traits<I1>::iterator_category, 
	      typename Op::result_type, 
	      typename std::iterator_traits<I1>::difference_type, 
	      typename Op::result_type*,
	      typename Op::result_type&>
{ 
public: 
  typedef Join_input_iterator_2<I1,I2,Op> Self;
  typedef typename Op::result_type value_type;
  typedef typename std::iterator_traits<I1>::difference_type difference_type; 
  typedef value_type* pointer;
  typedef value_type& reference; 
  
protected:
  I1 i1;
  I2 i2;
  Op op;
  mutable value_type val;  // Note: mutable is needed because we want to
                           // return a reference in operator*() and
                           // operator[](int) below.
  
public:
  Join_input_iterator_2() {}
  Join_input_iterator_2(const Join_input_iterator_2& it)
    : i1(it.i1), i2(it.i2), op(it.op) {}
  Join_input_iterator_2(I1 i1,I2 i2,const Op& op=Op())
    : i1(i1), i2(i2), op(op) {}
  
  I1 current_iterator1() const { return i1; }
  I2 current_iterator2() const { return i2; }
  
  bool operator==(const Self& i) const {
    return i1 == i.i1 && i2 == i.i2;
  }
  bool operator!=(const Self& i) const { return !(*this == i); }
  bool operator< (const Self& i) const {
    return i1 < i.i1 && i2 < i.i2;
  }
  
  Join_input_iterator_2& operator=(const Join_input_iterator_2& it)
  {
    i1 = it.i1;
    i2 = it.i2;
    op = it.op;
    return *this;
  }

  const value_type& operator*() const { 
    val = op(*i1,*i2);
    return val;
  }
  
  Self& operator++(   ) {
    ++i1;
    ++i2;
    return *this;
  }
  Self  operator++(int) { Self tmp = *this; ++(*this); return tmp; }
  Self& operator--(   ) {
    --i1;
    --i2;
    return *this;
  }
  Self  operator--(int) { Self tmp = *this; --(*this); return tmp; }
  
  const value_type& operator[](difference_type i) const {
    val = op(i1[i],i2[i]);
    return val;
  }
  
  Self& operator+=(difference_type n) {
    i1 += n;
    i2 += n;
    return *this;
  }
  Self& operator-=(difference_type n) {
    i1 -= n;
    i2 -= n;
    return *this;
  }
  Self  operator+ (difference_type n) const {
    Self tmp = *this;
    return tmp += n;
  }
  Self  operator- (difference_type n) const {
    Self tmp = *this;
    return tmp -= n;
  }
  difference_type operator-(const Self& i) const { return i1 - i.i1; }
};

template <class I1,class I2,class I3,class Op>
class Join_input_iterator_3 : public 
std::iterator<typename std::iterator_traits<I1>::iterator_category, 
	      typename Op::result_type, 
	      typename std::iterator_traits<I1>::difference_type, 
	      typename Op::result_type*,
	      typename Op::result_type&>
{ 
public: 
  typedef Join_input_iterator_3<I1,I2,I3,Op> Self;
  typedef typename Op::result_type value_type;
  typedef typename std::iterator_traits<I1>::difference_type difference_type; 
  typedef value_type* pointer;
  typedef value_type& reference; 
  
protected:
  I1 i1;
  I2 i2;
  I3 i3;
  Op op;
  mutable value_type val;  // Note: mutable is needed because we want to
                           // return a reference in operator*() and
                           // operator[](int) below.
  
public:
  Join_input_iterator_3() {}
  Join_input_iterator_3(const Join_input_iterator_3& it)
    : i1(it.i1), i2(it.i2), i3(it.i3), op(it.op) {}
  Join_input_iterator_3(I1 i1,I2 i2,I3 i3,const Op& op=Op())
    : i1(i1), i2(i2), i3(i3), op(op) {}
  
  I1 current_iterator1() const { return i1; }
  I2 current_iterator2() const { return i2; }
  I2 current_iterator3() const { return i3; }
  
  bool operator==(const Self& i) const {
    return i1 == i.i1 && i2 == i.i2 && i3 == i.i3;
  }
  bool operator!=(const Self& i) const { return !(*this == i); }
  bool operator< (const Self& i) const {
    return i1 < i.i1 && i2 < i.i2 && i3 < i.i3;
  }
  
  Join_input_iterator_3& operator=(const Join_input_iterator_3& it)
  {
    i1 = it.i1;
    i2 = it.i1;
    i3 = it.i3;
    op = it.op;
    return *this;
  }

  const value_type& operator*() const { 
    val = op(*i1,*i2,*i3);
    return val;
  }
  
  Self& operator++(   ) {
    ++i1;
    ++i2;
    ++i3;
    return *this;
  }
  Self  operator++(int) { Self tmp = *this; ++(*this); return tmp; }
  Self& operator--(   ) {
    --i1;
    --i2;
    --i3;
    return *this;
  }
  Self  operator--(int) { Self tmp = *this; --(*this); return tmp; }
  
  const value_type& operator[](difference_type i) const {
    val = op(i1[i],i2[i],i3[i]);
    return val;
  }
  
  Self& operator+=(difference_type n) {
    i1 += n;
    i2 += n;
    i3 += n;
    return *this;
  }
  Self& operator-=(difference_type n) {
    i1 -= n;
    i2 -= n;
    i3 -= n;
    return *this;
  }
  Self  operator+ (difference_type n) const {
    Self tmp = *this;
    return tmp += n;
  }
  Self  operator- (difference_type n) const {
    Self tmp = *this;
    return tmp -= n;
  }
  difference_type operator-(const Self& i) const { return i1 - i.i1; }
};

template < class IC>
class Inverse_index {

  // DEFINITION
  //
  // The class Inverse_index<IC,T> constructs an inverse index for a
  // given range [i,j) of two iterators or circulators of type `IC' with the
  // value type `T'. The first element I in the
  // range [i,j) has the index 0. Consecutive elements are numbered
  // incrementally. The inverse index provides a query for a given iterator
  // or circulator k to retrieve its index number. For random access
  // iterators or circulators, it is done in constant time by subtracting i.
  // For other iterator categories, an STL `map' is used, which results in a
  // log j-i query time. A comparison operator `operator<' is needed for
  // `T*'.
  //
  // CREATION

protected:
  typedef std::map< const void*, std::size_t >  Index;
  Index   idx;
  IC      start;
  typedef typename Index::iterator        Index_iterator;
  typedef typename Index::const_iterator  Index_const_iterator;
  typedef typename Index::value_type      Item;

protected:
  void ini_idx( IC i, const IC& j, std::input_iterator_tag);
  void ini_idx( const IC& i, const IC& j, std::forward_iterator_tag){
    ini_idx( i, j, std::input_iterator_tag());
  }
  void ini_idx(const IC& i,const IC& j, std::bidirectional_iterator_tag){
    ini_idx( i, j, std::input_iterator_tag());
  }
  void ini_idx( const IC& i, const IC& j, Forward_circulator_tag) {
    ini_idx( i, j, std::input_iterator_tag());
  }
  void ini_idx( const IC& i, const IC& j, Bidirectional_circulator_tag){
    ini_idx( i, j, std::input_iterator_tag());
  }
  void ini_idx( const IC&, const IC&, std::random_access_iterator_tag){}
  void ini_idx( const IC&, const IC&, Random_access_circulator_tag){}

public:
  void init_index( const IC& i, const IC& j) {
    typedef typename std::iterator_traits<IC>::iterator_category ICC;
    ini_idx( i, j, ICC());
  }

protected:
  void push_back( const IC& k, std::input_iterator_tag) {
    std::size_t d = idx.size();
    idx[ &*k] = d;
  }
  void push_back( const IC& k, std::forward_iterator_tag){
    push_back( k, std::input_iterator_tag());
  }
  void push_back( const IC& k, std::bidirectional_iterator_tag){
    push_back( k, std::input_iterator_tag());
  }
  void push_back( const IC& k, Forward_circulator_tag){
    push_back( k, std::input_iterator_tag());
  }
  void push_back( const IC& k, Bidirectional_circulator_tag){
    push_back( k, std::input_iterator_tag());
  }
  void push_back( const IC&, std::random_access_iterator_tag){}
  void push_back( const IC&, Random_access_circulator_tag){}

public:
  void push_back( const IC& k) {
    // adds k at the end of the indices.
    typedef typename std::iterator_traits<IC>::iterator_category ICC;
    push_back( k, ICC());
  }

  std::size_t find( const IC& k, std::random_access_iterator_tag) const {
    return std::size_t(k - start);
  }
  std::size_t find( const IC& k, Random_access_circulator_tag) const {
    return std::size_t(k - start);
  }
  std::size_t find( const IC& k, std::input_iterator_tag) const {
    // returns inverse index of k.
    Index_const_iterator i = idx.find( &*k);
    CGAL_assertion( i != idx.end());
    return (*i).second;
  }
  std::size_t find( const IC& k, std::forward_iterator_tag) const {
    return find( k, std::input_iterator_tag());
  }
  std::size_t find( const IC& k, std::bidirectional_iterator_tag) const {
    return find( k, std::input_iterator_tag());
  }
  std::size_t find( const IC& k, Forward_circulator_tag) const {
    return find( k, std::input_iterator_tag());
  }
  std::size_t find( const IC& k, Bidirectional_circulator_tag) const {
    return find( k, std::input_iterator_tag());
  }

  typedef IC           iterator;
  typedef IC           Circulator;
  typedef std::size_t  size_type;

  Inverse_index() : start(IC()) {}
  // invalid index.

  Inverse_index( const IC& i) : start(i) {};
  // empty inverse index initialized to start at i.

  Inverse_index( const IC& i, const IC& j) : start(i) {
    // inverse index initialized with range [i,j).
    init_index( i, j);
  }

  // OPERATIONS

  std::size_t operator[]( const IC& k) const {
    // returns inverse index of k.
    typedef typename std::iterator_traits<IC>::iterator_category
      category;
    return find( k, category());
  }
};

template < class IC>
void
Inverse_index< IC>::ini_idx( IC i, const IC& j, std::input_iterator_tag) {
  std::size_t n = 0;
  Index_iterator hint = idx.begin();
  if ( ! is_empty_range( i, j)) {
    do {
      hint = idx.insert( hint, Item( &*i, n));
      n++;
    } while ((++i) != (j));
  }
}

template < class IC>
class Random_access_adaptor {

  // DEFINITION
  //
  // The class Random_access_adaptor<IC> provides a random access
  // for data structures. Either the data structure supports random access
  // iterators or circulators where this class maps function calls to the
  // iterator or circulator, or a STL `vector' is used to provide the random
  // access. The iterator or circulator of the data structure are of type
  // `IC'.
  //
  // CREATION

protected:
  typedef std::vector< IC> Index;
  Index   index;
  IC      start;

public:
  typedef typename Index::size_type  size_type;

  void init_index( IC i, const IC& j, std::forward_iterator_tag);
  void init_index( const IC& i, const IC& j,
                   std::bidirectional_iterator_tag){
    init_index( i, j, std::forward_iterator_tag());
  }
  void init_index( const IC& i, const IC&,
                   std::random_access_iterator_tag){
    start = i;
  }
  void init_index( const IC& i, const IC& j) {
    typedef typename std::iterator_traits<IC>::iterator_category ICC;
    init_index( i, j, ICC());
  }


  void reserve( size_type r, std::forward_iterator_tag) {
    index.reserve( r);
  }
  void reserve( size_type r, std::bidirectional_iterator_tag){
    reserve( r, std::forward_iterator_tag());
  }
  void reserve( size_type, std::random_access_iterator_tag){}


  void push_back( const IC& k, std::forward_iterator_tag) {
    index.push_back(k);
  }
  void push_back( const IC& k, std::bidirectional_iterator_tag){
    push_back( k, std::forward_iterator_tag());
  }
  void push_back( const IC&, std::random_access_iterator_tag){}


  const IC& find( size_type n, std::forward_iterator_tag) const {
    // returns inverse index of k.
    CGAL_assertion( n < index.size());
    return index[n];
  }
  const IC& find( size_type n, std::bidirectional_iterator_tag) const {
    return find( n, std::forward_iterator_tag());
  }
  IC  find( size_type n, std::random_access_iterator_tag) const {
    return start + n;
  }

  typedef IC   iterator;
  typedef IC   Circulator;

  Random_access_adaptor() : start(IC()) {}
  // invalid index.

  Random_access_adaptor( const IC& i) : start(i) {}
  // empty random access index initialized to start at i.

  Random_access_adaptor( const IC& i, const IC& j) : start(i) {
    // random access index initialized with range [i,j).
    init_index( i, j);
  }

  void reserve( size_type r) {
    // reserve r entries, if a `vector' is used internally.
    typedef typename std::iterator_traits<IC>::iterator_category ICC;
    reserve( r, ICC());
  }

  // OPERATIONS

  IC  find( size_type n) const {
    // returns inverse index of k.
    typedef typename std::iterator_traits<IC>::iterator_category ICC;
    return find( n, ICC());
  }

  IC  operator[]( size_type n) const { return find(n); }

  void push_back( const IC& k) {
    // adds k at the end of the indices.
    typedef typename std::iterator_traits<IC>::iterator_category ICC;
    push_back( k, ICC());
  }
};

template < class IC>
void
Random_access_adaptor< IC>::init_index( IC i, const IC& j,
                                        std::forward_iterator_tag) {
  if ( ! is_empty_range( i, j)) {
    do {
      index.push_back( i);
    } while ((++i) != (j));
  }
}

template < class IC, class T >
class Random_access_value_adaptor : public Random_access_adaptor<IC> {
public:
  typedef typename Random_access_adaptor<IC>::size_type size_type;

  Random_access_value_adaptor() {}
  // invalid index.

  Random_access_value_adaptor( const IC& i)
  : Random_access_adaptor<IC>(i) {}
  // empty random access index initialized to start at i.

  Random_access_value_adaptor( const IC& i, const IC& j)
  : Random_access_adaptor<IC>(i,j) {}
  // random access index initialized with range [i,j).

  // OPERATIONS

  T& operator[]( size_type n) const {
    // returns inverse index of k.
    return *(Random_access_adaptor<IC>::operator[](n));
  }
};

template<typename _Iterator, typename Predicate>
    class Filter_output_iterator
    : public std::iterator<std::output_iterator_tag, void, void, void, void>
    {
    protected:
      _Iterator iterator;
      Predicate predicate;

    public:
      typedef _Iterator          iterator_type;

      explicit Filter_output_iterator(_Iterator& __x, const Predicate& pred) 
	: iterator(__x), predicate(pred) 
      {}

      template <typename T>
      Filter_output_iterator&
      operator=(const T& t)
      {
	if(! predicate(t))
	  *iterator = t;
	return *this;
      }

      Filter_output_iterator&
      operator*()
      { return *this; }

      Filter_output_iterator&
      operator++()
      { 
        ++iterator;
        return *this; 
      }

      Filter_output_iterator
      operator++(int)
      {
        Filter_output_iterator res(*this);
        ++iterator;
        return res; 
      }
    };

template < class I, class P >
inline Filter_output_iterator< I, P >
filter_output_iterator(I e, const P& p)
{ return Filter_output_iterator< I, P >(e, p); }


#ifndef CGAL_CFG_NO_CPP0X_VARIADIC_TEMPLATES

namespace internal {

template < typename D, typename V = cpp0x::tuple<>, typename O = cpp0x::tuple<> >
struct Derivator
{
#ifndef CGAL_CFG_NO_CPP0X_DELETED_AND_DEFAULT_FUNCTIONS
  typedef Derivator<D, V, O> Self;
  Self& operator=(const Self&) = delete;
#endif
};

template < typename D, typename V1, typename O1, typename... V, typename... O>
struct Derivator<D, cpp0x::tuple<V1, V...>, cpp0x::tuple<O1, O...> >
  : public Derivator<D, cpp0x::tuple<V...>, cpp0x::tuple<O...> >
{
  typedef Derivator<D, cpp0x::tuple<V1, V...>, cpp0x::tuple<O1, O...> > Self;
  typedef Derivator<D, cpp0x::tuple<V...>, cpp0x::tuple<O...> > Base;

#ifndef CGAL_CFG_NO_CPP0X_DELETED_AND_DEFAULT_FUNCTIONS
  Self& operator=(const Self&) = delete;
#endif

  using Base::operator=;
  
  D& operator=(const V1& v)
  {
    * cpp0x::get< D::size - sizeof...(V) - 1 >(static_cast<typename D::Iterator_tuple&>(static_cast<D&>(*this))) ++ = v;
    return static_cast<D&>(*this);
  }
};

} // internal


// OutputIterator which accepts several types in *o++= and dispatches,
// wraps several other outputiterators, and dispatches accordingly.
template < typename V, typename O >
class Dispatch_output_iterator;

template < typename... V, typename... O >
class Dispatch_output_iterator < cpp0x::tuple<V...>, cpp0x::tuple<O...> >
 : private internal::Derivator<Dispatch_output_iterator< cpp0x::tuple<V...>, cpp0x::tuple<O...> >, cpp0x::tuple<V...>, cpp0x::tuple<O...> >
 , public cpp0x::tuple<O...>
{
  static_assert(sizeof...(V) == sizeof...(O),
                "The number of explicit template parameters has to match the number of arguments");

  static const int size = sizeof...(V);

  template <typename D, typename V_, typename O_>
  friend class internal::Derivator;

public:

  typedef cpp0x::tuple<O...>               Iterator_tuple;
  typedef cpp0x::tuple<V...>               Value_type_tuple;

  typedef std::output_iterator_tag  iterator_category;
  typedef void                      value_type;
  typedef void                      difference_type;
  typedef void                      pointer;
  typedef void                      reference;

private:

  typedef Dispatch_output_iterator Self;
  typedef internal::Derivator<Self, Value_type_tuple, Iterator_tuple > Base;

public:

  using Base::operator=;

  Dispatch_output_iterator(O... o) : cpp0x::tuple<O...>(o...) {}

  Self& operator=(const Self& s)
  {
    static_cast<Iterator_tuple&>(*this) = static_cast<const Iterator_tuple&>(s);
    return *this;
  }

  Self& operator++() { return *this; }
  Self& operator++(int) { return *this; }
  Self& operator*() { return *this; }

  const Iterator_tuple& get_iterator_tuple() const { return *this; }
};

template < typename... V, typename... O>
Dispatch_output_iterator<cpp0x::tuple<V...>, cpp0x::tuple<O...> >
dispatch_output(O... o)
{
  return Dispatch_output_iterator<cpp0x::tuple<V...>, cpp0x::tuple<O...> > (o...);
}


// Same as Dispatch_output_iterator, but has a dummy *o++= for all other types
// that drops the data (same as Emptyset_iterator).

template < typename V, typename O >
class Dispatch_or_drop_output_iterator;

template < typename... V, typename... O >
class Dispatch_or_drop_output_iterator < cpp0x::tuple<V...>, cpp0x::tuple<O...> >
 : public Dispatch_output_iterator< cpp0x::tuple<V...>, cpp0x::tuple<O...> >
{
  typedef Dispatch_or_drop_output_iterator Self;
  typedef Dispatch_output_iterator< cpp0x::tuple<V...>, cpp0x::tuple<O...> > Base;

  template <typename D, typename V_, typename O_>
  friend class internal::Derivator;

public:

  Dispatch_or_drop_output_iterator(O... o) : Base(o...) {}

  using Base::operator=;

  Self& operator*() { return *this; }
  Self& operator++() { return *this; }
  Self& operator++(int) { return *this; }

  template <class T>
  Self& operator=(const T&) { return *this; }
};


template < typename... V, typename... O>
inline
Dispatch_or_drop_output_iterator<cpp0x::tuple<V...>, cpp0x::tuple<O...> >
dispatch_or_drop_output(O... o)
{
  return Dispatch_or_drop_output_iterator<cpp0x::tuple<V...>, cpp0x::tuple<O...> >(o...);
}

#else

// Non-variadic version

template < typename V, typename O >
class Dispatch_output_iterator;

template < typename V, typename O >
class Dispatch_or_drop_output_iterator;


// Version with 1 parameters
template<class V1,class O1>
class Dispatch_output_iterator<cpp0x::tuple<V1>,cpp0x::tuple<O1> >:public cpp0x::tuple<O1>{
  typedef Dispatch_output_iterator Self;
  
public:
  typedef cpp0x::tuple<V1> Value_type_tuple;
  typedef cpp0x::tuple<O1> Iterator_tuple;
  typedef std::output_iterator_tag iterator_category;
  typedef void                     value_type;
  typedef void                     difference_type;
  typedef void                     pointer;
  typedef void                     reference;


  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_output_iterator(O1 out1):Iterator_tuple(out1){}
    
  //Added because required by MSVC10
  Dispatch_output_iterator(const Self& other):
    Iterator_tuple(static_cast<const Iterator_tuple&>(other))
  {}
  
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }
  
  const Iterator_tuple& get_iterator_tuple() const
  { return *this; }
  
};


template<class V1,class O1>
inline 
Dispatch_output_iterator<cpp0x::tuple<V1>,cpp0x::tuple<O1> >
dispatch_output(O1 out1){
  return Dispatch_output_iterator<cpp0x::tuple<V1>,cpp0x::tuple<O1> >(out1);
}

//Version with DROP

template<class V1,class O1>
class Dispatch_or_drop_output_iterator<cpp0x::tuple<V1>,cpp0x::tuple<O1> >:
        public Dispatch_output_iterator<cpp0x::tuple<V1>,cpp0x::tuple<O1> >
{
  typedef Dispatch_or_drop_output_iterator Self;
  typedef Dispatch_output_iterator<cpp0x::tuple<V1>,cpp0x::tuple<O1> > Base;
  
public:

  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_or_drop_output_iterator(O1 out1):Base(out1){}
  
  #if defined(__EDG__)  
  typedef cpp0x::tuple<O1> Iterator_tuple;
    
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }    
  #else
  using Base::operator=;
  #endif //defined(__EDG__)
  
  
  template <class T>
  Self& operator=(const T&){
    return *this;
  }
};

template<class V1,class O1>
inline 
Dispatch_or_drop_output_iterator<cpp0x::tuple<V1>,cpp0x::tuple<O1> >
dispatch_or_drop_output(O1 out1){
  return Dispatch_or_drop_output_iterator<cpp0x::tuple<V1>,cpp0x::tuple<O1> >(out1);
}

// Version with 2 parameters
template<class V1,class O1,class V2,class O2>
class Dispatch_output_iterator<cpp0x::tuple<V1,V2>,cpp0x::tuple<O1,O2> >:public cpp0x::tuple<O1,O2>{
  typedef Dispatch_output_iterator Self;
  
public:
  typedef cpp0x::tuple<V1,V2> Value_type_tuple;
  typedef cpp0x::tuple<O1,O2> Iterator_tuple;
  typedef std::output_iterator_tag iterator_category;
  typedef void                     value_type;
  typedef void                     difference_type;
  typedef void                     pointer;
  typedef void                     reference;


  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_output_iterator(O1 out1,O2 out2):Iterator_tuple(out1,out2){}

  //Added because required by MSVC10
  Dispatch_output_iterator(const Self& other):
    Iterator_tuple(static_cast<const Iterator_tuple&>(other))
  {}

  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }
  
  const Iterator_tuple& get_iterator_tuple() const
  { return *this; }
  
};


template<class V1,class V2,class O1,class O2>
inline 
Dispatch_output_iterator<cpp0x::tuple<V1,V2>,cpp0x::tuple<O1,O2> >
dispatch_output(O1 out1,O2 out2){
  return Dispatch_output_iterator<cpp0x::tuple<V1,V2>,cpp0x::tuple<O1,O2> >(out1,out2);
}

//Version with DROP

template<class V1,class O1,class V2,class O2>
class Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2>,cpp0x::tuple<O1,O2> >:
        public Dispatch_output_iterator<cpp0x::tuple<V1,V2>,cpp0x::tuple<O1,O2> >
{
  typedef Dispatch_or_drop_output_iterator Self;
  typedef Dispatch_output_iterator<cpp0x::tuple<V1,V2>,cpp0x::tuple<O1,O2> > Base;
  
public:

  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_or_drop_output_iterator(O1 out1,O2 out2):Base(out1,out2){}
  
  #if defined(__EDG__)  
  typedef cpp0x::tuple<O1,O2> Iterator_tuple;
    
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }    
  #else
  using Base::operator=;
  #endif //defined(__EDG__)
  
  
  template <class T>
  Self& operator=(const T&){
    return *this;
  }
};

template<class V1,class V2,class O1,class O2>
inline 
Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2>,cpp0x::tuple<O1,O2> >
dispatch_or_drop_output(O1 out1,O2 out2){
  return Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2>,cpp0x::tuple<O1,O2> >(out1,out2);
}

//Version with 3 parameters
template<class V1,class O1,class V2,class O2,class V3, class O3>
class Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3>,cpp0x::tuple<O1,O2,O3> >:public cpp0x::tuple<O1,O2,O3>{
  typedef Dispatch_output_iterator Self;
  
public:
  typedef cpp0x::tuple<V1,V2,V3> Value_type_tuple;
  typedef cpp0x::tuple<O1,O2,O3> Iterator_tuple;
  typedef std::output_iterator_tag iterator_category;
  typedef void                     value_type;
  typedef void                     difference_type;
  typedef void                     pointer;
  typedef void                     reference;


  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_output_iterator(O1 out1,O2 out2,O3 out3):Iterator_tuple(out1,out2,out3){}

  //Added because required by MSVC10
  Dispatch_output_iterator(const Self& other):
    Iterator_tuple(static_cast<const Iterator_tuple&>(other))
  {}  

  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }

  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }
  
  const Iterator_tuple& get_iterator_tuple() const
  { return *this; }
  
};


template<class V1,class V2,class V3,class O1,class O2,class O3>
inline 
Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3>,cpp0x::tuple<O1,O2,O3> >
dispatch_output(O1 out1,O2 out2,O3 out3){
  return Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3>,cpp0x::tuple<O1,O2,O3> >(out1,out2,out3);
}

//Version with DROP
template < typename V, typename O >
class Dispatch_or_drop_output_iterator;


template<class V1,class O1,class V2,class O2,class V3,class O3>
class Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3>,cpp0x::tuple<O1,O2,O3> >:
        public Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3>,cpp0x::tuple<O1,O2,O3> >
{
  typedef Dispatch_or_drop_output_iterator Self;
  typedef Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3>,cpp0x::tuple<O1,O2,O3> > Base;
  
public:

  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_or_drop_output_iterator(O1 out1,O2 out2,O3 out3):Base(out1,out2,out3){}
  
  #if defined(__EDG__)  
  typedef cpp0x::tuple<O1,O2,O3> Iterator_tuple;
    
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }    
  #else
  using Base::operator=;
  #endif //defined(__EDG__)
  
  
  template <class T>
  Self& operator=(const T&){
    return *this;
  }
};

template<class V1,class V2,class V3,class O1,class O2,class O3>
inline 
Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3>,cpp0x::tuple<O1,O2,O3> >
dispatch_or_drop_output(O1 out1,O2 out2,O3 out3){
  return Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3>,cpp0x::tuple<O1,O2,O3> >(out1,out2,out3);
}

//Version with 4 parameters
template<class V1,class O1,class V2,class O2,class V3,class O3,class V4,class O4>
class Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4>,cpp0x::tuple<O1,O2,O3,O4> >:public cpp0x::tuple<O1,O2,O3,O4>{
  typedef Dispatch_output_iterator Self;
  
public:
  typedef cpp0x::tuple<V1,V2,V3,V4> Value_type_tuple;
  typedef cpp0x::tuple<O1,O2,O3,O4> Iterator_tuple;
  typedef std::output_iterator_tag iterator_category;
  typedef void                     value_type;
  typedef void                     difference_type;
  typedef void                     pointer;
  typedef void                     reference;


  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_output_iterator(O1 out1,O2 out2,O3 out3,O4 out4):Iterator_tuple(out1,out2,out3,out4){}

  //Added because required by MSVC10
  Dispatch_output_iterator(const Self& other):
    Iterator_tuple(static_cast<const Iterator_tuple&>(other))
  {}  
  
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }

  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V4& obj){
    *cpp0x::get<3>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }
  
  const Iterator_tuple& get_iterator_tuple() const
  { return *this; }
  
};


template<class V1,class V2,class V3,class V4,class O1,class O2,class O3,class O4>
inline 
Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4>,cpp0x::tuple<O1,O2,O3,O4> >
dispatch_output(O1 out1,O2 out2,O3 out3,O4 out4){
  return Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4>,cpp0x::tuple<O1,O2,O3,O4> >(out1,out2,out3,out4);
}

//Version with DROP
template < typename V, typename O >
class Dispatch_or_drop_output_iterator;


template<class V1,class O1,class V2,class O2,class V3,class O3,class V4,class O4>
class Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4>,cpp0x::tuple<O1,O2,O3,O4> >:
        public Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4>,cpp0x::tuple<O1,O2,O3,O4> >
{
  typedef Dispatch_or_drop_output_iterator Self;
  typedef Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4>,cpp0x::tuple<O1,O2,O3,O4> > Base;
  
public:

  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_or_drop_output_iterator(O1 out1,O2 out2,O3 out3,O4 out4):Base(out1,out2,out3,out4){}
  
  #if defined(__EDG__)  
  typedef cpp0x::tuple<O1,O2,O3,O4> Iterator_tuple;
    
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V4& obj){
    *cpp0x::get<3>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }    
  #else
  using Base::operator=;
  #endif //defined(__EDG__)
  
  
  template <class T>
  Self& operator=(const T&){
    return *this;
  }
};

template<class V1,class V2,class V3,class V4,class O1,class O2,class O3,class O4>
inline 
Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4>,cpp0x::tuple<O1,O2,O3,O4> >
dispatch_or_drop_output(O1 out1,O2 out2,O3 out3,O4 out4){
  return Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4>,cpp0x::tuple<O1,O2,O3,O4> >(out1,out2,out3,out4);
}

//Version with 5 parameters
template<class V1,class O1,class V2,class O2,class V3,class O3,class V4,class O4,class V5,class O5>
class Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5>,cpp0x::tuple<O1,O2,O3,O4,O5> >:public cpp0x::tuple<O1,O2,O3,O4,O5>{
  typedef Dispatch_output_iterator Self;
  
public:
  typedef cpp0x::tuple<V1,V2,V3,V4,V5> Value_type_tuple;
  typedef cpp0x::tuple<O1,O2,O3,O4,O5> Iterator_tuple;
  typedef std::output_iterator_tag iterator_category;
  typedef void                     value_type;
  typedef void                     difference_type;
  typedef void                     pointer;
  typedef void                     reference;


  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_output_iterator(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5):Iterator_tuple(out1,out2,out3,out4,out5){}

  //Added because required by MSVC10
  Dispatch_output_iterator(const Self& other):
    Iterator_tuple(static_cast<const Iterator_tuple&>(other))
  {}  
  
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }

  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V4& obj){
    *cpp0x::get<3>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V5& obj){
    *cpp0x::get<4>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }
  
  const Iterator_tuple& get_iterator_tuple() const
  { return *this; }
  
};


template<class V1,class V2,class V3,class V4,class V5,class O1,class O2,class O3,class O4,class O5>
inline 
Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5>,cpp0x::tuple<O1,O2,O3,O4,O5> >
dispatch_output(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5){
  return Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5>,cpp0x::tuple<O1,O2,O3,O4,O5> >(out1,out2,out3,out4,out5);
}

//Version with DROP
template < typename V, typename O >
class Dispatch_or_drop_output_iterator;


template<class V1,class O1,class V2,class O2,class V3,class O3,class V4,class O4,class V5,class O5>
class Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5>,cpp0x::tuple<O1,O2,O3,O4,O5> >:
        public Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5>,cpp0x::tuple<O1,O2,O3,O4,O5> >
{
  typedef Dispatch_or_drop_output_iterator Self;
  typedef Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5>,cpp0x::tuple<O1,O2,O3,O4,O5> > Base;
  
public:

  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_or_drop_output_iterator(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5):Base(out1,out2,out3,out4,out5){}
  
  #if defined(__EDG__)  
  typedef cpp0x::tuple<O1,O2,O3,O4,O5> Iterator_tuple;
    
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V4& obj){
    *cpp0x::get<3>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V5& obj){
    *cpp0x::get<4>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }    
  #else
  using Base::operator=;
  #endif //defined(__EDG__)
  
  
  template <class T>
  Self& operator=(const T&){
    return *this;
  }
};

template<class V1,class V2,class V3,class V4,class V5,class O1,class O2,class O3,class O4,class O5>
inline 
Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5>,cpp0x::tuple<O1,O2,O3,O4,O5> >
dispatch_or_drop_output(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5){
  return Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5>,cpp0x::tuple<O1,O2,O3,O4,O5> >(out1,out2,out3,out4,out5);
}

//Version with 6 parameters
template<class V1,class O1,class V2,class O2,class V3,class O3,class V4,class O4,class V5,class O5,class V6,class O6>
class Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6>,cpp0x::tuple<O1,O2,O3,O4,O5,O6> >:public cpp0x::tuple<O1,O2,O3,O4,O5,O6>{
  typedef Dispatch_output_iterator Self;
  
public:
  typedef cpp0x::tuple<V1,V2,V3,V4,V5,V6> Value_type_tuple;
  typedef cpp0x::tuple<O1,O2,O3,O4,O5,O6> Iterator_tuple;
  typedef std::output_iterator_tag iterator_category;
  typedef void                     value_type;
  typedef void                     difference_type;
  typedef void                     pointer;
  typedef void                     reference;


  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_output_iterator(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5,O6 out6):Iterator_tuple(out1,out2,out3,out4,out5,out6){}

  //Added because required by MSVC10
  Dispatch_output_iterator(const Self& other):
    Iterator_tuple(static_cast<const Iterator_tuple&>(other))
  {}  
  
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }

  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V4& obj){
    *cpp0x::get<3>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V5& obj){
    *cpp0x::get<4>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V6& obj){
    *cpp0x::get<5>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }
  
  const Iterator_tuple& get_iterator_tuple() const
  { return *this; }
  
};


template<class V1,class V2,class V3,class V4,class V5,class V6,class O1,class O2,class O3,class O4,class O5,class O6>
inline 
Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6>,cpp0x::tuple<O1,O2,O3,O4,O5,O6> >
dispatch_output(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5,O6 out6){
  return Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6>,cpp0x::tuple<O1,O2,O3,O4,O5,O6> >(out1,out2,out3,out4,out5,out6);
}

//Version with DROP
template < typename V, typename O >
class Dispatch_or_drop_output_iterator;


template<class V1,class O1,class V2,class O2,class V3,class O3,class V4,class O4,class V5,class O5,class V6,class O6>
class Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6>,cpp0x::tuple<O1,O2,O3,O4,O5,O6> >:
        public Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6>,cpp0x::tuple<O1,O2,O3,O4,O5,O6> >
{
  typedef Dispatch_or_drop_output_iterator Self;
  typedef Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6>,cpp0x::tuple<O1,O2,O3,O4,O5,O6> > Base;
  
public:

  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_or_drop_output_iterator(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5,O6 out6):Base(out1,out2,out3,out4,out5,out6){}
  
  #if defined(__EDG__)  
  typedef cpp0x::tuple<O1,O2,O3,O4,O5,O6> Iterator_tuple;
    
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V4& obj){
    *cpp0x::get<3>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V5& obj){
    *cpp0x::get<4>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V6& obj){
    *cpp0x::get<5>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }    
  #else
  using Base::operator=;
  #endif //defined(__EDG__)
  
  
  template <class T>
  Self& operator=(const T&){
    return *this;
  }
};

template<class V1,class V2,class V3,class V4,class V5,class V6,class O1,class O2,class O3,class O4,class O5,class O6>
inline 
Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6>,cpp0x::tuple<O1,O2,O3,O4,O5,O6> >
dispatch_or_drop_output(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5,O6 out6){
  return Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6>,cpp0x::tuple<O1,O2,O3,O4,O5,O6> >(out1,out2,out3,out4,out5,out6);
}

//Version with 7 parameters
template<class V1,class O1,class V2,class O2,class V3,class O3,class V4,class O4,class V5,class O5,class V6,class O6,class V7,class O7>
class Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7>,cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> >:public cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7>{
  typedef Dispatch_output_iterator Self;
  
public:
  typedef cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7> Value_type_tuple;
  typedef cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> Iterator_tuple;
  typedef std::output_iterator_tag iterator_category;
  typedef void                     value_type;
  typedef void                     difference_type;
  typedef void                     pointer;
  typedef void                     reference;


  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_output_iterator(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5,O6 out6,O7 out7):Iterator_tuple(out1,out2,out3,out4,out5,out6,out7){}

  //Added because required by MSVC10
  Dispatch_output_iterator(const Self& other):
    Iterator_tuple(static_cast<const Iterator_tuple&>(other))
  {}  
  
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }

  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V4& obj){
    *cpp0x::get<3>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V5& obj){
    *cpp0x::get<4>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V6& obj){
    *cpp0x::get<5>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
   Self& operator=(const V7& obj){
    *cpp0x::get<6>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }
  
  const Iterator_tuple& get_iterator_tuple() const
  { return *this; }
  
};


template<class V1,class V2,class V3,class V4,class V5,class V6,class V7,class O1,class O2,class O3,class O4,class O5,class O6,class O7>
inline 
Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7>,cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> >
dispatch_output(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5,O6 out6,O7 out7){
  return Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7>,cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> >(out1,out2,out3,out4,out5,out6,out7);
}

//Version with DROP
template < typename V, typename O >
class Dispatch_or_drop_output_iterator;


template<class V1,class O1,class V2,class O2,class V3,class O3,class V4,class O4,class V5,class O5,class V6,class O6,class V7,class O7>
class Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7>,cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> >:
        public Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7>,cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> >
{
  typedef Dispatch_or_drop_output_iterator Self;
  typedef Dispatch_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7>,cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> > Base;
  
public:

  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; } 
  Self& operator++(int){ return *this; }  
  
  Dispatch_or_drop_output_iterator(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5,O6 out6,O7 out7):Base(out1,out2,out3,out4,out5,out6,out7){}
  
  #if defined(__EDG__)  
  typedef cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> Iterator_tuple;
    
  Self& operator=(const V1& obj){
    *cpp0x::get<0>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }
  
  Self& operator=(const V2& obj){
    *cpp0x::get<1>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V3& obj){
    *cpp0x::get<2>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V4& obj){
    *cpp0x::get<3>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V5& obj){
    *cpp0x::get<4>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const V6& obj){
    *cpp0x::get<5>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  

  Self& operator=(const V7& obj){
    *cpp0x::get<6>(static_cast<Iterator_tuple& >(*this))++=obj;
    return *this;
  }  
  
  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }    
  #else
  using Base::operator=;
  #endif //defined(__EDG__)
  
  
  template <class T>
  Self& operator=(const T&){
    return *this;
  }
};

template<class V1,class V2,class V3,class V4,class V5,class V6,class V7,class O1,class O2,class O3,class O4,class O5,class O6,class O7>
inline 
Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7>,cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> >
dispatch_or_drop_output(O1 out1,O2 out2,O3 out3,O4 out4,O5 out5,O6 out6,O7 out7){
  return Dispatch_or_drop_output_iterator<cpp0x::tuple<V1,V2,V3,V4,V5,V6,V7>,cpp0x::tuple<O1,O2,O3,O4,O5,O6,O7> >(out1,out2,out3,out4,out5,out6,out7);
}

#endif

} //namespace CGAL

#if defined(BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif // CGAL_ITERATOR_H
