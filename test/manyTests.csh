#### Source this file


#cmsRun muonTest_cfg.py print files_load=zmm_3_2_5.list output='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_zmm_2_5_all.root' maxEvents=-1 > & ! ~/scratch0/test_zmm.log 

#cmsRun muonTest_cfg.py print files_load=singleMu10.list output='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_singleMu10_2_5_all.root' maxEvents=-1 > & ! ~/scratch0/test_singleMu.log 

#cmsRun muonTest_cfg.py print files_load=jpsi.list output='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_jpsi_all.root' maxEvents=-1 > & ! ~/scratch0/test_jpsi.log 

#cmsRun muonTest_cfg.py print files_load=ttbar_3_1_0_pre9.list output='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_ttbar_2_5_all.root' maxEvents=-1 > & ! ~/scratch0/test_ttbar.log 

#cmsRun muonTest_cfg.py print files_load=jpsi_330_pre3.list output='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_jpsi_330_pre3_newMem.root' maxEvents=2000 > & ! ~/scratch0/test_jpsi.log

#cmsRun quadJetTest_cfg.py print files_load=ttbar_3_1_0_pre9.list output='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_ttbar_qjet_test.root' maxEvents=10 > & ! ~/scratch0/test_qjet.log 

cmsRun muonTest_cfg.py print files_load=tt_oct.list output='file:/data/ndpc0/b/slaunwhj/scratch0/EDM_ttbar_oct.root' maxEvents=-1 > & ! /data/ndpc0/b/slaunwhj/scratch0/test_ttbar.log
