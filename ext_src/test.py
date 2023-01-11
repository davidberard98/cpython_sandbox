import dberard

dberard.system("ls -lha")

# instantiate animal, this should print some debug about a new "Animal"
a = dberard.Animal()

class Cat(dberard.Animal):
    def __repr__(self):
        return "Cat()"

# instantiate cat, this will print some debug about a new "Cat"
# i.e. showing that from C++ we know that this is a different type...
c = Cat()
