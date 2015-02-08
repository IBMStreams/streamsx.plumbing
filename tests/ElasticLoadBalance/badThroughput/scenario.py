import testharness as th

def test():
    stdout, stderr, err = th.make_standalone()
    th.assert_pass(err != 0 and 
                   stderr.find('ERROR: The throughputTolerance param must be a value between 0.0 and 1.0.') != -1,
                   stdout, stderr)

