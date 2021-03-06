/******************************************************************************
The MIT License(MIT)

Embedded Template Library.

Copyright(c) 2014 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include <UnitTest++/UnitTest++.h>

#include "../deque.h"

#include <vector>
#include <algorithm>

const size_t SIZE = 6;

typedef etl::deque<int, SIZE> Data;
typedef std::vector<int>      Compare_Data;

namespace
{		
	SUITE(test_deque)
	{
    //*************************************************************************
		TEST(test_constructor)
		{
      Data data;

      CHECK_EQUAL(SIZE, data.capacity());
      CHECK_EQUAL(SIZE, data.max_size());
		}

    //*************************************************************************
    TEST(test_constructor_fill)
    {
      Compare_Data compare_data = { 5, 5, 5, 5, 5, 5};
      Data data(SIZE, 5);

      CHECK_EQUAL(compare_data.size(), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_constructor_fill_excess)
    {
      CHECK_THROW(Data(SIZE + 1, 5), etl::deque_full);
    }

    //*************************************************************************
    TEST(test_constructor_range)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data(compare_data.begin(), compare_data.end());

      CHECK_EQUAL(compare_data.size(), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_constructor_range_excess)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5, 6, 7 };
      
      CHECK_THROW(Data data(compare_data.begin(), compare_data.end()), etl::deque_full);
    }

    //*************************************************************************
		TEST(test_copy_constructor)
		{
      Compare_Data compare_data = { 1, 2, 3, 4, 5, 6 };
      Compare_Data modified = { 6, 5, 4, 3, 2, 1 };
     
      Data deque1(compare_data.begin(), compare_data.end());
      Data deque2(deque1);

      CHECK_EQUAL(deque1.size(), deque2.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), deque2.begin()));
		}

    //*************************************************************************
		TEST(test_assignment)
		{
      Compare_Data compare_data = { 1, 2, 3, 4, 5, 6 };
     
      Data deque1(compare_data.begin(), compare_data.end());
      Data deque2;
      
      deque2 = deque1;

      CHECK_EQUAL(deque1.size(), deque2.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), deque2.begin()));
		}

    //*************************************************************************
    TEST(test_assign_range)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data;

      CHECK_NO_THROW(data.assign(compare_data.begin(), compare_data.end()));

      CHECK_EQUAL(compare_data.size(), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_assign_range_excess)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5, 6, 7 };
      Data data;

      CHECK_THROW(data.assign(compare_data.begin(), compare_data.end()), etl::deque_full);
    }

    //*************************************************************************
    TEST(test_assign_fill)
    {
      Compare_Data compare_data = { 5, 5, 5, 5, 5, 5 };

      Data data;

      CHECK_NO_THROW(data.assign(SIZE, 5));

      CHECK_EQUAL(compare_data.size(), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_assign_fill_excess)
    {
      Data data;

      CHECK_THROW(data.assign(SIZE + 1, 5), etl::deque_full);
    }

    //*************************************************************************
    TEST(test_at)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data(compare_data.begin(), compare_data.end());

      CHECK_EQUAL(compare_data[0], data.at(0));
      CHECK_EQUAL(compare_data[1], data.at(1));
      CHECK_EQUAL(compare_data[2], data.at(2));
      CHECK_EQUAL(compare_data[3], data.at(3));
      CHECK_EQUAL(compare_data[4], data.at(4));
    }

    //*************************************************************************
    TEST(test_at_const)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data(compare_data.begin(), compare_data.end());
      const Data& cdata(data);

      CHECK_EQUAL(compare_data[0], cdata.at(0));
      CHECK_EQUAL(compare_data[1], cdata.at(1));
      CHECK_EQUAL(compare_data[2], cdata.at(2));
      CHECK_EQUAL(compare_data[3], cdata.at(3));
      CHECK_EQUAL(compare_data[4], cdata.at(4));
    }

    //*************************************************************************
    TEST(test_index_operator)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data(compare_data.begin(), compare_data.end());

      CHECK_EQUAL(compare_data[0], data[0]);
      CHECK_EQUAL(compare_data[1], data[1]);
      CHECK_EQUAL(compare_data[2], data[2]);
      CHECK_EQUAL(compare_data[3], data[3]);
      CHECK_EQUAL(compare_data[4], data[4]);
    }

    //*************************************************************************
    TEST(test_index_operator_const)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data(compare_data.begin(), compare_data.end());
      const Data& ctestDeque(data);

      CHECK_EQUAL(compare_data[0], ctestDeque[0]);
      CHECK_EQUAL(compare_data[1], ctestDeque[1]);
      CHECK_EQUAL(compare_data[2], ctestDeque[2]);
      CHECK_EQUAL(compare_data[3], ctestDeque[3]);
      CHECK_EQUAL(compare_data[4], ctestDeque[4]);
    }
    
    //*************************************************************************
    TEST(test_front)
    {
      Data data;

      data.push_front(1);
      CHECK_EQUAL(1, data.front());

      data.push_front(2);
      CHECK_EQUAL(2, data.front());

      data.push_front(3);
      CHECK_EQUAL(3, data.front());

      data.push_front(4);
      CHECK_EQUAL(4, data.front());

      data.push_front(5);
      CHECK_EQUAL(5, data.front());
    }

    //*************************************************************************
    TEST(test_front_const)
    {
      Data data;
      const Data& ctestDeque = data;

      data.push_front(1);
      CHECK_EQUAL(1, ctestDeque.front());

      data.push_front(2);
      CHECK_EQUAL(2, ctestDeque.front());

      data.push_front(3);
      CHECK_EQUAL(3, ctestDeque.front());

      data.push_front(4);
      CHECK_EQUAL(4, ctestDeque.front());

      data.push_front(5);
      CHECK_EQUAL(5, ctestDeque.front());
    }

    //*************************************************************************
    TEST(test_back)
    {
      Data data;

      data.push_back(1);
      CHECK_EQUAL(1, data.back());

      data.push_back(2);
      CHECK_EQUAL(2, data.back());

      data.push_back(3);
      CHECK_EQUAL(3, data.back());

      data.push_back(4);
      CHECK_EQUAL(4, data.back());

      data.push_back(5);
      CHECK_EQUAL(5, data.back());
    }

    //*************************************************************************
    TEST(test_back_const)
    {
      Data data;
      const Data& ctestDeque = data;

      data.push_back(1);
      CHECK_EQUAL(1, ctestDeque.back());

      data.push_back(2);
      CHECK_EQUAL(2, ctestDeque.back());

      data.push_back(3);
      CHECK_EQUAL(3, ctestDeque.back());

      data.push_back(4);
      CHECK_EQUAL(4, ctestDeque.back());

      data.push_back(5);
      CHECK_EQUAL(5, ctestDeque.back());
    }

    //*************************************************************************
    TEST(test_iterator_comparison)
    {
      Data data(6, 0);

      Data::iterator first = data.begin() + 1;
      Data::iterator second = data.begin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_const_iterator_comparison)
    {
      Data data(6, 0);

      Data::const_iterator first = data.cbegin() + 1;
      Data::const_iterator second = data.cbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_iterator_comparison_rollover_left)
    {
      Data data(6, 0);

      data.pop_back();
      data.pop_back();
      data.pop_back();
      data.push_front(1);
      data.push_front(1);
      data.push_front(1);

      Data::const_iterator first = data.cbegin() + 1;
      Data::const_iterator second = data.cbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_const_iterator_comparison_rollover_left)
    {
      Data data(6, 0);

      data.pop_back();
      data.pop_back();
      data.pop_back();
      data.push_front(1);
      data.push_front(1);
      data.push_front(1);

      Data::const_iterator first = data.cbegin() + 1;
      Data::const_iterator second = data.cbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_iterator_comparison_rollover_right)
    {
      Data data(6, 0);

      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.push_back(1);
      data.push_back(1);
      data.push_back(1);

      Data::iterator first = data.begin() + 1;
      Data::iterator second = data.begin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_const_iterator_comparison_rollover_right)
    {
      Data data(6, 0);

      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.push_back(1);
      data.push_back(1);
      data.push_back(1);

      Data::const_iterator first = data.cbegin() + 1;
      Data::const_iterator second = data.cbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_reverse_iterator_comparison)
    {
      Data data(6, 0);

      Data::reverse_iterator first = data.rbegin() + 1;
      Data::reverse_iterator second = data.rbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_const_reverse_iterator_comparison)
    {
      Data data(6, 0);

      Data::const_reverse_iterator first = data.crbegin() + 1;
      Data::const_reverse_iterator second = data.crbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_reverse_iterator_comparison_rollover_left)
    {
      Data data(6, 0);

      data.pop_back();
      data.pop_back();
      data.pop_back();
      data.push_front(1);
      data.push_front(1);
      data.push_front(1);

      Data::reverse_iterator first = data.rbegin() + 1;
      Data::reverse_iterator second = data.rbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_const_reverse_iterator_comparison_rollover_left)
    {
      Data data(6, 0);

      data.pop_back();
      data.pop_back();
      data.pop_back();
      data.push_front(1);
      data.push_front(1);
      data.push_front(1);

      Data::const_reverse_iterator first = data.crbegin() + 1;
      Data::const_reverse_iterator second = data.crbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_reverse_iterator_comparison_rollover_right)
    {
      Data data(6, 0);

      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.push_back(1);
      data.push_back(1);
      data.push_back(1);

      Data::reverse_iterator first = data.rbegin() + 1;
      Data::reverse_iterator second = data.rbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_const_reverse_iterator_comparison_rollover_right)
    {
      Data data(6, 0);

      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.push_back(1);
      data.push_back(1);
      data.push_back(1);

      Data::const_reverse_iterator first = data.crbegin() + 1;
      Data::const_reverse_iterator second = data.crbegin() + 4;

      CHECK(first < second);
      CHECK(!(second < first));
    }

    //*************************************************************************
    TEST(test_empty)
    {
      Data data;

      CHECK(data.empty());
    }

    //*************************************************************************
    TEST(test_full)
    {
      Data data;
      data.resize(SIZE);

      CHECK(data.full());
    }

    //*************************************************************************
    TEST(test_clear)
    {
      Data data;

      data.resize(SIZE);
      data.clear();
      CHECK(data.empty());
    }

    //*************************************************************************
    TEST(test_insert_value_begin)
    {
      Compare_Data compare_data = { 1, 2, 3, 4 };
      Compare_Data expected = { 5, 1, 2, 3, 4 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.begin(), 5);

      CHECK_EQUAL(expected.size(), data.size());
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
      CHECK_EQUAL(0, std::distance(data.begin(), position));
    }

    //*************************************************************************
    TEST(test_insert_value_end)
    {
      Compare_Data compare_data = { 1, 2, 3, 4 };
      Compare_Data expected = { 1, 2, 3, 4, 5 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.end(), 5);

      CHECK_EQUAL(expected.size(), data.size());
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
      CHECK_EQUAL(4, std::distance(data.begin(), position));
    }

    //*************************************************************************
    TEST(test_insert_value_middle)
    {
      Compare_Data compare_data = { 1, 2, 3, 4 };
      Compare_Data expected1 = { 1, 5, 2, 3, 4 };
      Compare_Data expected2 = { 1, 2, 5, 3, 4 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.begin() + 1, 5);

      CHECK_EQUAL(expected1.size(), data.size());
      CHECK(std::equal(expected1.begin(), expected1.end(), data.begin()));
      CHECK_EQUAL(1, std::distance(data.begin(), position));

      data.assign(compare_data.begin(), compare_data.end());

      position = data.insert(data.begin() + 2, 5);

      CHECK_EQUAL(expected2.size(), data.size());
      CHECK(std::equal(expected2.begin(), expected2.end(), data.begin()));
      CHECK_EQUAL(2, std::distance(data.begin(), position));
    }

    //*************************************************************************
    TEST(test_insert_n_value_begin)
    {
      Compare_Data compare_data = { 1, 2, 3 };
      Compare_Data expected = { 5, 5, 1, 2, 3 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.begin(), 2, 5);

      CHECK_EQUAL(expected.size(), data.size());
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
      CHECK_EQUAL(0, std::distance(data.begin(), position));
    }

    //*************************************************************************
    TEST(test_insert_n_value_end)
    {
      Compare_Data compare_data = { 1, 2, 3 };
      Compare_Data expected = { 1, 2, 3, 5, 5 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.end(), 2, 5);

      CHECK_EQUAL(expected.size(), data.size());
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
      CHECK_EQUAL(3, std::distance(data.begin(), position));
    }

    //*************************************************************************
    TEST(test_insert_n_value_middle)
    {
      Compare_Data compare_data = { 1, 2, 3, 4 };
      Compare_Data expected1 = { 1, 5, 5, 2, 3, 4 };
      Compare_Data expected2 = { 1, 2, 3, 5, 5, 4 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.begin() + 1, 2, 5);

      CHECK_EQUAL(expected1.size(), data.size());
      CHECK(std::equal(expected1.begin(), expected1.end(), data.begin()));
      CHECK_EQUAL(1, std::distance(data.begin(), position));

      data.assign(data.max_size(), -1);
      data.assign(compare_data.begin(), compare_data.end());

      position = data.insert(data.begin() + 3, 2, 5);

      CHECK_EQUAL(expected2.size(), data.size());
      CHECK(std::equal(expected2.begin(), expected2.end(), data.begin()));
      CHECK_EQUAL(3, std::distance(data.begin(), position));
    }

    //*************************************************************************
    TEST(test_insert_n_value_excess)
    {
      Compare_Data compare_data = { 1, 2, 3, 4 };
      Data data(compare_data.begin(), compare_data.end());

      CHECK_THROW(data.insert(data.begin(), 3, 5), etl::deque_full);
      CHECK_THROW(data.insert(data.end(), 3, 5), etl::deque_full);
      CHECK_THROW(data.insert(data.begin() + 2, 3, 5), etl::deque_full);
    }

    //*************************************************************************
    TEST(test_insert_range_begin)
    {
      Compare_Data compare_data = { 1, 2, 3 };
      Compare_Data range = { 4, 5 };
      Compare_Data expected = { 4, 5, 1, 2, 3 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.begin(), range.begin(), range.end());

      CHECK_EQUAL(expected.size(), data.size());
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_insert_range_end)
    {
      Compare_Data compare_data = { 1, 2, 3 };
      Compare_Data range = { 4, 5 };
      Compare_Data expected = { 1, 2, 3, 4, 5 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.end(), range.cbegin(), range.cend());

      CHECK_EQUAL(expected.size(), data.size());
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_insert_range_middle)
    {
      Compare_Data compare_data = { 1, 2, 3, 4 };
      Compare_Data range = { 5, 6 };
      Compare_Data expected1 = { 1, 5, 6, 2, 3, 4 };
      Compare_Data expected2 = { 1, 2, 3, 5, 6, 4 };
      Data data(compare_data.begin(), compare_data.end());

      Data::iterator position = data.insert(data.begin() + 1, range.begin(), range.end());

      CHECK_EQUAL(expected1.size(), data.size());
      CHECK(std::equal(expected1.begin(), expected1.end(), data.begin()));
      CHECK_EQUAL(1, std::distance(data.begin(), position));

      data.assign(compare_data.begin(), compare_data.end());

      position = data.insert(data.begin() + 3, range.begin(), range.end());

      CHECK_EQUAL(expected2.size(), data.size());
      CHECK(std::equal(expected2.begin(), expected2.end(), data.begin()));
      CHECK_EQUAL(3, std::distance(data.begin(), position));
    }

    //*************************************************************************
    TEST(test_insert_range_excess)
    {
      Compare_Data compare_data = { 1, 2, 3, 4 };
      Compare_Data range = { 5, 6, 7 };
      Data data(compare_data.begin(), compare_data.end());

      CHECK_THROW(data.insert(data.begin(), range.begin(), range.end()), etl::deque_full);
      CHECK_THROW(data.insert(data.end(), range.begin(), range.end()), etl::deque_full);
      CHECK_THROW(data.insert(data.begin() + 2, range.begin(), range.end()), etl::deque_full);
    }

    //*************************************************************************
    TEST(test_erase_begin)
    {
      Compare_Data compare_data = { 0, 0, 1, 2, 3, 4 };
      Compare_Data expected = { 2, 3, 4, 5, 6 };
      Data data(compare_data.begin(), compare_data.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.push_back(5);
      data.push_back(6);

      Data::iterator i_next = data.erase(data.begin());

      CHECK_EQUAL(Data::difference_type(expected.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), data.begin().get_index());
    }

    //*************************************************************************
    TEST(test_erase_end)
    {
      Compare_Data compare_data = { 0, 0, 1, 2, 3, 4 };
      Compare_Data expected = { 1, 2, 3, 4, 5 };
      Data data(compare_data.begin(), compare_data.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.push_back(5);
      data.push_back(6);

      Data::iterator i_erase = data.end() - 1;
      Data::iterator i_next = data.erase(i_erase);

      CHECK_EQUAL(Data::difference_type(expected.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), data.end().get_index());
    }

    //*************************************************************************
    TEST(test_erase_middle)
    {
      Compare_Data compare_data = { 0, 0, 1, 2, 3, 4 };
      Compare_Data expected1 = { 1, 3, 4, 5, 6 };
      Compare_Data expected2 = { 1, 2, 3, 4, 6 };

      Data data(compare_data.begin(), compare_data.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.push_back(5);
      data.push_back(6);

      // Erase near beginning.
      Data::iterator i_erase = data.begin() + 1;
      Data::iterator i_next = data.erase(i_erase);

      CHECK_EQUAL(Data::difference_type(expected1.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected1.begin(), expected1.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), data.begin().get_index() + 1);

      data.assign(compare_data.begin(), compare_data.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.push_back(5);
      data.push_back(6);

      // Erase near end.
      i_next = data.erase(data.begin() + 4);

      CHECK_EQUAL(Data::difference_type(expected2.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected2.begin(), expected2.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), data.begin().get_index() + 4);
    }

    //*************************************************************************
    TEST(test_erase_range_begin)
    {
      Compare_Data compare_data = { 0, 0, 1, 2, 3, 4 };
      Compare_Data expected = { 3, 4, 5, 6 };
      Data data(compare_data.begin(), compare_data.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.push_back(5);
      data.push_back(6);

      Data::iterator i_next = data.erase(data.begin(), data.begin() + 2);

      CHECK_EQUAL(Data::difference_type(expected.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), data.begin().get_index());
    }

    //*************************************************************************
    TEST(test_erase_range_end)
    {
      Compare_Data compare_data = { 0, 0, 1, 2, 3, 4 };
      Compare_Data expected = { 1, 2, 3, 4 };
      Data data(compare_data.begin(), compare_data.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.push_back(5);
      data.push_back(6);

      Data::iterator i_next = data.erase(data.end() - 2, data.end());

      CHECK_EQUAL(Data::difference_type(expected.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected.begin(), expected.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), data.end().get_index());
    }

    //*************************************************************************
    TEST(test_erase_range_middle)
    {
      Compare_Data compare_data = { 0, 0, 1, 2, 3, 4 };
      Compare_Data expected1 = { 1, 4, 5, 6 };
      Compare_Data expected2 = { 1, 2, 3, 6 };

      Data data(compare_data.begin(), compare_data.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.push_back(5);
      data.push_back(6);

      Data::iterator i_next = data.erase(data.begin() + 1, data.begin() + 3);

      CHECK_EQUAL(Data::difference_type(expected1.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected1.begin(), expected1.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), (data.begin() + 1).get_index());

      data.assign(compare_data.begin(), compare_data.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.push_back(5);
      data.push_back(6);

      i_next = data.erase(data.begin() + 3, data.begin() + 5);

      CHECK_EQUAL(Data::difference_type(expected2.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected2.begin(), expected2.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), (data.begin() + 3).get_index());

      Compare_Data original2 = { 0, 0, 0, 0, 1, 2 };
      Compare_Data expected3 = { 1, 2, 5, 6 };

      data.assign(original2.begin(), original2.end());

      // Cause rollover.
      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.push_back(3);
      data.push_back(4);
      data.push_back(5);
      data.push_back(6);

      i_next = data.erase(data.begin() + 2, data.begin() + 4);

      CHECK_EQUAL(Data::difference_type(expected3.size()), std::distance(data.begin(), data.end()));
      CHECK(std::equal(expected3.begin(), expected3.end(), data.begin()));
      CHECK_EQUAL(i_next.get_index(), (data.begin() + 2).get_index());
    }

    //*************************************************************************
    TEST(test_push_back_null)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data;

      CHECK_NO_THROW(data.push_back());
      CHECK_NO_THROW(data.back() = 1);
      CHECK_EQUAL(size_t(1), data.size());

      CHECK_NO_THROW(data.push_back());
      CHECK_NO_THROW(data.back() = 2);
      CHECK_EQUAL(size_t(2), data.size());

      CHECK_NO_THROW(data.push_back());
      CHECK_NO_THROW(data.back() = 3);
      CHECK_EQUAL(size_t(3), data.size());

      CHECK_NO_THROW(data.push_back());
      CHECK_NO_THROW(data.back() = 4);
      CHECK_EQUAL(size_t(4), data.size());

      CHECK_NO_THROW(data.push_back());
      CHECK_NO_THROW(data.back() = 5);
      CHECK_EQUAL(size_t(5), data.size());

      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_push_back)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5};
      Data data;

      CHECK_NO_THROW(data.push_back(1));
      CHECK_EQUAL(size_t(1), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end() - 4, data.begin()));

      CHECK_NO_THROW(data.push_back(2));
      CHECK_EQUAL(size_t(2), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end() - 3, data.begin()));

      CHECK_NO_THROW(data.push_back(3));
      CHECK_EQUAL(size_t(3), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end() - 2, data.begin()));

      CHECK_NO_THROW(data.push_back(4));
      CHECK_EQUAL(size_t(4), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end() - 1, data.begin()));

      CHECK_NO_THROW(data.push_back(5));
      CHECK_EQUAL(size_t(5), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_push_back_excess)
    {
      Data data;

      CHECK_NO_THROW(data.push_back(1));
      CHECK_NO_THROW(data.push_back(2));
      CHECK_NO_THROW(data.push_back(3));
      CHECK_NO_THROW(data.push_back(4));
      CHECK_NO_THROW(data.push_back(5));
      CHECK_NO_THROW(data.push_back(6));
      CHECK_THROW(data.push_back(7), etl::deque_full);
    }

    //*************************************************************************
    TEST(test_pop_back)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data;

      data.assign(compare_data.begin(), compare_data.end());

      data.pop_back();
      CHECK_EQUAL(size_t(4), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end() - 1, data.begin()));

      data.pop_back();
      CHECK_EQUAL(size_t(3), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end() - 2, data.begin()));

      data.pop_back();
      CHECK_EQUAL(size_t(2), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end() - 3, data.begin()));

      data.pop_back();
      CHECK_EQUAL(size_t(1), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end() - 4, data.begin()));

      data.pop_back();
      CHECK_EQUAL(size_t(0), data.size());
    }

    //*************************************************************************
    TEST(test_push_front_null)
    {
      Compare_Data compare_data = {5,  4, 3, 2, 1 };
      Data data;

      CHECK_NO_THROW(data.push_front());
      CHECK_NO_THROW(data.front() = 1);
      CHECK_EQUAL(size_t(1), data.size());

      CHECK_NO_THROW(data.push_front());
      CHECK_NO_THROW(data.front() = 2);
      CHECK_EQUAL(size_t(2), data.size());

      CHECK_NO_THROW(data.push_front());
      CHECK_NO_THROW(data.front() = 3);
      CHECK_EQUAL(size_t(3), data.size());

      CHECK_NO_THROW(data.push_front());
      CHECK_NO_THROW(data.front() = 4);
      CHECK_EQUAL(size_t(4), data.size());

      CHECK_NO_THROW(data.push_front());
      CHECK_NO_THROW(data.front() = 5);
      CHECK_EQUAL(size_t(5), data.size());

      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_push_front)
    {
      Compare_Data compare_data = { 5, 4, 3, 2, 1 };
      Data data;

      CHECK_NO_THROW(data.push_front(1));
      CHECK_EQUAL(size_t(1), data.size());
      CHECK(std::equal(compare_data.begin() + 4, compare_data.end(), data.begin()));

      CHECK_NO_THROW(data.push_front(2));
      CHECK_EQUAL(size_t(2), data.size());
      CHECK(std::equal(compare_data.begin() + 3, compare_data.end(), data.begin()));

      CHECK_NO_THROW(data.push_front(3));
      CHECK_EQUAL(size_t(3), data.size());
      CHECK(std::equal(compare_data.begin() + 2, compare_data.end(), data.begin()));

      CHECK_NO_THROW(data.push_front(4));
      CHECK_EQUAL(size_t(4), data.size());
      CHECK(std::equal(compare_data.begin() + 1, compare_data.end(), data.begin()));

      CHECK_NO_THROW(data.push_front(5));
      CHECK_EQUAL(size_t(5), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_push_front_excess)
    {
      Data data;

      for (size_t i = 0; i < SIZE; ++i)
      {
        CHECK_NO_THROW(data.push_front(i));
      }

      CHECK_THROW(data.push_front(SIZE), etl::deque_full);
    }

    //*************************************************************************
    TEST(test_push_front_push_back)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5};
      Data data;

      CHECK_NO_THROW(data.push_back(3));
      CHECK_NO_THROW(data.push_front(2));
      CHECK_NO_THROW(data.push_back(4));
      CHECK_NO_THROW(data.push_front(1));
      CHECK_NO_THROW(data.push_back(5));

      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_push_back_pop_front_push_back)
    {
      Compare_Data compare_data = { 6, 7, 8 };
      Data data;

      data.push_back(1);
      data.push_back(2);
      data.push_back(3);
      data.push_back(4);
      data.push_back(5);
      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.push_back(6);
      data.push_back(7);
      data.push_back(8);

      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_pop_front)
    {
      Compare_Data compare_data = { 1, 2, 3, 4, 5 };
      Data data;

      data.assign(compare_data.begin(), compare_data.end());

      data.pop_front();
      CHECK_EQUAL(size_t(4), data.size());
      CHECK(std::equal(compare_data.begin() + 1, compare_data.end(), data.begin()));

      data.pop_front();
      CHECK_EQUAL(size_t(3), data.size());
      CHECK(std::equal(compare_data.begin() + 2, compare_data.end(), data.begin()));

      data.pop_front();
      CHECK_EQUAL(size_t(2), data.size());
      CHECK(std::equal(compare_data.begin() + 3, compare_data.end(), data.begin()));

      data.pop_front();
      CHECK_EQUAL(size_t(1), data.size());
      CHECK(std::equal(compare_data.begin() + 4, compare_data.end(), data.begin()));

      data.pop_front();
      CHECK_EQUAL(size_t(0), data.size());
    }

    //*************************************************************************
    TEST(test_resize_up)
    {
      Compare_Data compare_data = { 1, 2, 0, 0, 0 };
      Data data;

      // Cause rollover.
      data.push_back(0);
      data.push_back(0);
      data.push_back(0);
      data.push_back(0);
      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.push_back(1);
      data.push_back(2);
      data.resize(SIZE);

      CHECK_EQUAL(size_t(SIZE), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_resize_down)
    {
      Compare_Data compare_data = { 1, 2 };
      Data data;

      // Cause rollover.
      data.push_back(0);
      data.push_back(0);
      data.push_back(0);
      data.pop_front();
      data.pop_front();
      data.pop_front();
      data.push_back(1);
      data.push_back(2);
      data.push_back(3);
      data.push_back(4);
      data.push_back(5);
      data.push_back(6);
      data.resize(data.size() - 4);

      CHECK_EQUAL(size_t(2), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_resize_value)
    {
      Compare_Data compare_data = { 1, 2, 3, 3, 3 };
      Data data;

      data.push_front(1);
      data.push_back(2);
      data.resize(SIZE, 3);

      CHECK_EQUAL(size_t(SIZE), data.size());
      CHECK(std::equal(compare_data.begin(), compare_data.end(), data.begin()));
    }

    //*************************************************************************
    TEST(test_resize_excess)
    {
      Data data;

      CHECK_THROW(data.resize(SIZE + 1), etl::deque_out_of_bounds);
    }

    //*************************************************************************
    TEST(test_swap)
    {
      Compare_Data compare_data1 = { 1, 2, 3, 4, 5, 6 };
      Compare_Data compare_data2 = { 6, 5, 4 };

      Data data1(compare_data1.begin(), compare_data1.end());
      Data data2(compare_data2.begin(), compare_data2.end());

      swap(data1, data2);

      CHECK_EQUAL(compare_data2.size(), data1.size());
      CHECK_EQUAL(compare_data1.size(), data2.size());

      CHECK_EQUAL(std::distance(compare_data2.begin(), compare_data2.end()), std::distance(data1.begin(), data1.end()));
      CHECK_EQUAL(std::distance(compare_data1.begin(), compare_data1.end()), std::distance(data2.begin(), data2.end()));

      CHECK(std::equal(compare_data2.begin(), compare_data2.end(), data1.begin()));
      CHECK(std::equal(compare_data1.begin(), compare_data1.end(), data2.begin()));
    }

    //*************************************************************************
		TEST(test_equality_operator)
		{
      Compare_Data same      = { 1, 2, 3, 4, 5, 6 };
      Compare_Data different = { 6, 5, 4, 3, 2, 1 };
     
      Data deque1(same.begin(), same.end());
      Data deque2(deque1);

      CHECK(deque1 == deque2);

      // Change deque2's data.
      std::copy(different.begin(), different.end(), deque2.begin());

      CHECK(!(deque1 == deque2));
		}

    //*************************************************************************
    TEST(test_inequality_operator)
    {
      Compare_Data same = { 1, 2, 3, 4, 5, 6 };
      Compare_Data different = { 6, 5, 4, 3, 2, 1 };

      Data deque1(same.begin(), same.end());
      Data deque2(deque1);

      CHECK(!(deque1 != deque2));

      // Change deque2's data.
      std::copy(different.begin(), different.end(), deque2.begin());

      CHECK(deque1 != deque2);
    }
	};
}
