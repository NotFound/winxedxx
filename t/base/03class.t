#! winxed

// winxedxx base tests
// class

using extern Test.More plan, is;

class Foo
{
    var value;
    function Foo(int i)
    {
        self.value = i;
    }
    function get()
    {
        if (self.value != null)
            return self.value;
        else
	    return 27;
    }
}

namespace Bar
{

class FooBar
{
    var n;
    function FooBar(int i)
    {
        self.n = i * 10;
    }
    function get()
    {
        int i;
        if (self.n != null)
	    i = self.n;
        else
	    i = 7;
	return i;
    }
}

class Parent { }

class Foo : Parent
{
    function Foo()
    {
    }
    function get()
    {
        return 3;
    }
}

} // namespace Bar

function main [main] (var args)
{
    plan(5);

    var foo = new Foo(42);
    int i = foo.get();
    is(i, 42, "new simple with argument");
    foo = new Foo;
    i = foo.get();
    is(i, 27, "new simple without constructor call");
    foo = new Bar.FooBar(42);
    i = foo.get();
    is(i, 420, "new qualified new with argument");
    foo = new Bar.FooBar;
    i = foo.get();
    is(i, 7, "new qualified without constructor call");
    foo = new Bar.Foo();
    i = foo.get();
    is(i, 3, "class with same name in other namespace");
}

// End
