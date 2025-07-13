# get the root path
my_dir = os.path.dirname(__file__)
print "root path: %s" % my_dir


# tests list, suppose that files are on the same folder 
tests = [
          "serv100_tst_001.py", 
          "serv100_tst_002.py",
          "serv100_tst_003.py",
          "serv100_tst_004.py",
          "serv100_tst_005.py",
          "serv100_tst_006.py",
          "serv100_tst_007.py",
          "serv100_tst_008.py",
         ]

# this will be a dictionary that stores all test results 
results = {}

logging.info("starting test suite")

for test in tests:
    logging.info("starting test %s" % test)
    try: 
        execfile(os.path.join(my_dir, test))
    except Exception as e:
        logging.error("%s failed" % test)
        logging.exception(e) # log exception
        results[test] = "fail"
        execfile(os.path.join(my_dir, "test_fail.py"))
    else:
        logging.info("test ok (no exceptions)")
        results[test] = "ok"
 
logging.info("test suite is done")
for test, result in results.items():
    print "%s : %s" % (test, result)
    
    































