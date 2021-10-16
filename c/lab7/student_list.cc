/*
 * Idenitfy all the memory bugs and potential bugs in this code
 */

#include <string>

struct Student {
  std::string name_;
  std::uint64_t phone_;
  Student* next_;
};

//void delete_list1(Student* head)  // Bad: we just delete the first element, so all next Student objects get leaked.
//{
//    delete head;
//}

//void delete_list2(Student* head)   // Bad: we delete the head element, so we can't access the next property of it.
//{
//  while(head) {
//    delete head;
//    head = head->next_;
//  }
//}

//void delete_list3(Student* head)  // Bad: Almost the same as above. After deleting head, we can't access the next property of it.
//{
//  while(head->next_) {
//    delete head;
//    head = head->next_;
//  }
//}

//void delete_list4(Student* head)  // Bad: we never check for head being the nullptr, and we also never delete head if next pointer doesn't point to anything.
//{
//  while(head->next_) {
//    Student* tmp = head->next_;
//    delete head;
//    head = tmp;
//  }
//}

void delete_list5(Student* head)  // Correct!!!!
{
  if (!head) {
    return;
  }
  while(head->next_) {
    Student* tmp = head->next_;
    delete head;
    head = tmp;
  }
  delete head;
}

void delete_list6(Student* head)  // Bad, not an array
{
  if (!head) {
    return;
  }
  while(head->next_) {
    Student* tmp = head->next_;
    delete head;
    head = tmp;
  }
  delete[] head;
}

void delete_list7(Student* head)  // Also correct
{
  if (!head) {
    return;
  }

  while(head->next_) {
    auto tmp = head->next_;
    delete head;
    head = tmp;
  }
  delete head;
}

void delete_list8(Student* head) // Bad, because in initial version we never deleted head after exiting the recursive function call.
{
  if (!head) return;
  if (head->next_) {
      delete_list8(head->next_);
  }
  delete head;
}

////////////////////////////////////////////////////////////////////////

int main()
{
  Student* lst;
  lst->name_ = "whoami"; // Bad: because we never initialized a student object and didn't give memory to store it
  delete lst;            // Bad: we didn't put a value to lst, so we can't delete it.
  delete_list1(lst);     // Bad: same as line above

  lst = new Student({ "Joe", 1234, nullptr });
  delete_list1(lst);    // Bad: if lst.next wasn't null, hten it would leak the next objects

  lst = new Student({ "Joe", 1234, nullptr });
  lst = new Student({ "Jolene", 4321, nullptr });  // Bad: we never clean the memory after allocating it for JOE
  delete_list2(lst);    // Bad: frees the memory and tries to accesss it, ud()
  delete_list3(lst);    // Bad: we already deleted head, wouldn't work, we also don't have next.

  lst = new Student({ "Jolene", 7332578, nullptr });
  delete_list3(lst);    // Bad: no head.next, doesn't delete anythin (memory leak)

  lst = new Student({ "Jeremy", 1, nullptr }); // Memory leak
  lst = new Student({ "Jolene", 90554, new Student() }); // Memory leak
  lst->name_ = "Joel";  // Fine

  lst->next_->name_ = "Jill";   // Okay
  lst->next_->next_->name_ = "Jack";  // next_->next_ is nullptr

  delete_list2(lst);  // head->next does not exist
  delete_list3(lst);  // head->next does not exist
  delete_list4(lst);  // we never delete head if next is nullptr
  delete_list5(lst);  // will work
  delete_list6(lst);  // it's not an array
  delete_list7(lst);  // correct
  delete_list8(lst);  // never delete head
  delete_list8(lst->next_);  // we never delete the head 


  return 0;
}
