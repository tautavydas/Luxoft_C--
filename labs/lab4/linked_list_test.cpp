#include "linked_list.h"
#include <gtest/gtest.h>

TEST(LinedListTest,InsertAt0) {
	LinkedList myList{1,2,3};
	LinkedList expectedList{2,1,2,3};

	myList.insertAt(0,2);

	ASSERT_EQ(myList,expectedList);

}

TEST(LinedListTest,InsertAt1) {
	LinkedList myList{1,2,3};
	LinkedList expectedList{1,2,2,3};

	myList.insertAt(1,2);

	ASSERT_EQ(myList,expectedList);

}

TEST(LinedListTest,RemoveAt1) {
	LinkedList myList{1,2,3};
	LinkedList expectedList{1,3};

	myList.removeAt(1);

	ASSERT_EQ(myList,expectedList);
}

TEST(LinedListTest,RemoveAt0) {
	LinkedList myList{1,2,3};
	LinkedList expectedList{2,3};

	myList.removeAt(0);

	ASSERT_EQ(myList,expectedList);

}

TEST(LinedListTest,RemoveAtLast) {
	LinkedList myList{1,2,3};
	LinkedList expectedList{1,2};

	myList.removeAt(2);

	ASSERT_EQ(myList,expectedList);
}


TEST(LinedListTest, CopyList) {
  LinkedList myList{ 1,2,3 };
  LinkedList copyList(myList);
  ASSERT_EQ(myList, copyList);
}


TEST(LinedListTest, CopyAndDelete) {
  auto list = new LinkedList{ 1,2,3 };
  LinkedList copyList(*list);
  delete list;

  copyList.insertAt(0, 0);
  LinkedList* copy2 = new LinkedList(*list);
  ASSERT_FALSE(copyList == *copy2);
  copy2->insertAt(0, 0);
  ASSERT_EQ(copyList, *copy2);
  delete copy2;
}