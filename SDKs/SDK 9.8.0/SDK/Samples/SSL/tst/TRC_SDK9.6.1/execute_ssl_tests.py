# get the root path
my_dir = os.path.dirname(__file__)
print "root path: %s" % my_dir


# tests list, suppose that files are on the same folder 
tests = [
          "ssl_pro_001.py", 
          "ssl_pro_002.py",
          "ssl_pro_003.py",
          "ssl_pro_004.py",
          "ssl_pro_005.py",
          "ssl_pro_006.py",
        ]

# this will be a dictionary that stores all test results 
results = {}

logging.info("starting test suite")
execfile(os.path.join(my_dir, "test_startupapp.py"))
for test in tests:
    logging.info("starting test %s" % test)
    try: 
        execfile(os.path.join(my_dir, "test_startup.py"))
        execfile(os.path.join(my_dir, test))
    except Exception as e:
        logging.error("%s failed" % test)
        logging.exception(e) # log exception
        results[test] = "fail"
        execfile(os.path.join(my_dir, "test_fail.py"))
        execfile(os.path.join(my_dir, "test_startupapp.py"))
    else:
        logging.info("test ok (no exceptions)")
        results[test] = "ok"
        #execfile(os.path.join(my_dir, "test_teardown.py"))
 
logging.info("test suite is done")
execfile(os.path.join(my_dir, "test_teardown.py"))
for test, result in results.items():
    print "%s : %s" % (test, result)
    
    




























