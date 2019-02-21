program main (input, output);

    var a,b: integer;
    var x,y,z: real;

    function foo(b: integer) : integer;
        var x: real;
        procedure bar(b: real);
        begin
            z := 2.718; {illegal}
        end;
    begin
        x := 3.14;
        bar(1.1);
        foo := 2*b
    end;

    procedure boo(p: integer; q: real);
        var a: real;
        var z: integer;
    begin
        writeln(p + 13);
        writeln(p + 13)
    end;

begin
    boo (13, 3.14);
end.