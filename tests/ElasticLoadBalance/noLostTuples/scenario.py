import testharness as th

def test():
    stdout, stderr, err = th.make_standalone(args=['elastic=true', 'initialActivePorts=1'])
    th.assert_pass(err == 0, stdout, stderr)

    stdout, stderr, err = th.run_standalone(args=['tuples=300000000'])
    th.assert_pass(err == 0 and 
                   stdout.rstrip() == 'pass', 
                   stdout, stderr)

    stdout, stderr, err = th.make_standalone(args=['elastic=true', 'initialActivePorts=3'])
    th.assert_pass(err == 0, stdout, stderr)

    stdout, stderr, err = th.run_standalone(args=['tuples=300000000'])
    th.assert_pass(err == 0 and 
                   stdout.rstrip() == 'pass', 
                   stdout, stderr)

    stdout, stderr, err = th.make_standalone(args=['elastic=false', 'initialActivePorts=1'])
    th.assert_pass(err == 0, stdout, stderr)

    stdout, stderr, err = th.run_standalone(args=['tuples=10000000'])
    th.assert_pass(err == 0 and 
                   stdout.rstrip() == 'pass', 
                   stdout, stderr)

    stdout, stderr, err = th.make_standalone(args=['elastic=false', 'initialActivePorts=4'])
    th.assert_pass(err == 0, stdout, stderr)

    stdout, stderr, err = th.run_standalone(args=['tuples=10000000'])
    th.assert_pass(err == 0 and 
                   stdout.rstrip() == 'pass', 
                   stdout, stderr)

