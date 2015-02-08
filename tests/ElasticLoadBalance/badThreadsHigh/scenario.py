import testharness as th

def test():
    stdout, stderr, err = th.make_standalone()
    th.assert_pass(err != 0 and 
                   stderr.find('ERROR: The initialActivePorts param must not be greater than the number of output ports.') != -1,
                   stdout, stderr)
