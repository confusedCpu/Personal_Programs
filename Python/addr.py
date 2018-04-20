#!/usr/bin/python3
# addr.py
# This is a simple application to keep track of contact information from the terminal

import os
import re
import shutil
import sys

DEFAULT_PATH = os.path.join(os.path.expanduser('~'),  '.addr_book')
DEFAULT_BACKUP_PATH = os.path.join(os.path.expanduser('~'), '.addr_book_backup')

class Contact:
    def __init__(self, name='Unkown', homep='Unkown', cellp='Unkown', workp='Unkown',
                 emailp='Unkown', emailw='Unkown'):
      self.name = str(name)
      self.homep = str(homep)
      self.cellp = str(cellp)
      self.workp = str(workp)
      self.emailp = str(emailp)
      self.emailw = str(emailw)

    def __itter__(self):
       return self

    def __str__(self):
        return 'name:{}, homep:{}, cellp:{}, workp:{}, emailp:{}, emailw:{}'.format(
                self.name, self.homep, self.cellp, self.workp, self.emailp, self.emailw)

    def display(self):
       print('''{0}
                   phone:
                      (h) {1}
                      (c) {2}
                      (w) {3}
                   email:
                      (p) {4}
                      (w) {5}\n'''.format(self.name, self.homep, self.cellp, self.workp,
                                       self.emailp, self.emailw))


def add_contact(contact_line):
    book = open_book()

    book.append(build_contact(contact_line))
    write_book(book)

def build_contact(line):
    copy = line
    name = re.search(r'(?<=name:)[a-zA-Z\s]*', line)            #contact name
    homep = re.search(r'(?<=homep:)[0-9\.\-\(\)x]*', line)      #contact home phone
    cellp = re.search(r'(?<=cellp:)[0-9\.\-\(\)x]*', line)      #contact cell phone
    workp = re.search(r'(?<=workp:)[0-9\.\-\(\)x]*', line)      #contact work phone
    emailp = re.search(r'(?<=emailp:)[a-zA-Z0-9\@\._]*', line)  #contact personal email
    emailw = re.search(r'(?<=emailw:)[a-zA-Z0-9\@\._]*', line)  #contact work email
    temp_contact = Contact()

    if name is not None:
        temp_contact.name = str(name.group(0))
    if homep is not None:
        temp_contact.homep = str(homep.group(0))
    if cellp is not None:
        temp_contact.cellp = str(cellp.group(0))
    if workp is not None:
        temp_contact.workp = str(workp.group(0))
    if emailp is not None:
        temp_contact.emailp = str(emailp.group(0))
    if emailw is not None:
        temp_contact.emailw = str(emailw.group(0))

    return temp_contact

def delete_contact(name):
    book = open_book()

    for contact in book:
        if contact.name == name:
            book.remove(contact)

    write_book(book)


def get_help():
    print('''This is a simple application to keep track of contact information from the terminal

             format:
               addr function [keys] [values]

             funtions:
               add    - create new contact
               delete - delete an existing contact
               print - search and print saved contact information
               update - update an existing contact

            contact keys (all string values):
              name    - first and last name
              cellp   - cell phone number
              homep   - home phone number
              workp   - work phone number
              workx   - work phone extention
              email   - email address

            examples:
              addr add {name:'John Doe', cellp:'555-555-5555', email:'user@domain.com'}
                   - creates a new contact

              addr delete 'John Doe'
                   - deletes John Doe's contact information

              addr print 'John Doe'
                   - prints John Doe's information

              addr update 'John Doe' 'homep:222-222-2222'
                   - updates an existing contact named 'John Doe' ''')

    sys.exit()

def open_book():
    if not os.path.isfile(DEFAULT_PATH):
        open(DEFAULT_PATH, 'w').close() # creates an addr_book file if one does not exist

    with open(DEFAULT_PATH) as f:
        contacts = [build_contact(line) for line in f]

    return contacts

def print_contact(query):
    book = open_book()

    if query == '*':
      [contact.display() for contact in book]
    else:
        for contact in book:
            if contact.name == query:
                contact.display()

def update_contact(name, key, value):
    book = open_book()

    for contact in book:
        print('{}'.format(contact.name))
        if contact.name == name:
            if key == 'name':
                contact.name = str(value)
            elif key == 'homep':
                contact.homep = str(value)
            elif key == 'cellp':
                contact.cellp = str(value)
            elif key == 'workp':
                contact.workp = str(value)
            elif key == 'emailp':
                contact.emailp = str(value)
            elif key == 'emailw':
                contact.emailw = str(value)
            else:
                print('The key you privided "{}", is not a valid key.'.format((str(key))))
                get_help()

    print('Contact updated, writing changes to address book')
    write_book(book)
    print('Done, exiting.')
    del book, temp
    sys.exit()

def write_book(contacts):
    shutil.copy2(DEFAULT_PATH, DEFAULT_BACKUP_PATH) # move original to backup file with metadata

    with open(DEFAULT_PATH, 'w') as book:
        for entry in contacts:
            book.write('{}\n'.format(str(entry)))

    sys.exit()

def main():
    if 3 > len(sys.argv):
        get_help()

    if sys.argv[1] == 'add':
        add_contact(str(sys.argv[2]))
    elif sys.argv[1] == 'delete':
        delete_contact(str(sys.argv[2]))
    elif sys.argv[1] == 'update':
        update_contact(str(sys.argv[2]), str(sys.argv[3]), str(sys.argv[4]))
    elif sys.argv[1] == 'print':
        print_contact(str(sys.argv[2]))
        sys.exit()

    print('There seems to have been some sort of issue, you were never supposed to make it this far')


# Statement to call the main function
if __name__ == '__main__':
    main()
