import testharness as th

def test():
    stdout, stderr, err = th.make_standalone()
    th.assert_pass(err != 0 and 
                   stderr.find('ERROR: The measurePeriod param must be greater than 0.') != -1,
                   stdout, stderr)
