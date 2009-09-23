#### Source this file

#cmsRun muonPostProcessor_cfg.py print files='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_zmm_2_5_all.root' output='file:/data/ndpc1/b/slaunwhj/scratch0/Histos_zmm_2_5_all.root' maxEvents=-1 >&! ~/scratch0/test_zmm_post.log
#cmsRun muonPostProcessor_cfg.py print files='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_ttbar_2_5_all.root' output='file:/data/ndpc1/b/slaunwhj/scratch0/Histos_ttbar_2_5_all.root' maxEvents=-1 > & ! ~/scratch0/test_ttbar_post.log 
#cmsRun muonPostProcessor_cfg.py print files='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_singleMu10_2_5_all.root' output='file:/data/ndpc1/b/slaunwhj/scratch0/Histos_singleMu10_2_5_all.root' maxEvents=-1 > & ! ~/scratch0/test_singleMu_post.log 

#cmsRun muonPostProcessor_cfg.py print files='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_craftSuperPointing.root' outputDir='/data/ndpc1/b/slaunwhj/scratch0/' maxEvents=-1 > & ! ~/scratch0/test_cosmics_post.log 
#cmsRun muonClientTest_cfg.py print files='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_ttbar_2_5_all.root' outputDir='/data/ndpc1/b/slaunwhj/scratch0/' workflow='/DQMGeneric/Test/Blah' maxEvents=-1 >&! ~/scratch0/test_top_post.log

cmsRun muonPostProcessor_cfg.py print files='file:/data/ndpc1/b/slaunwhj/scratch0/EDM_jpsi_330_pre3_numEvent10000.root' outputDir='/data/ndpc1/b/slaunwhj/scratch0/' workflow='/DQMGeneric/JPsi/3_3_0_pre4_v2' maxEvents=-1 >&! ~/scratch0/test_jpsi_post.log
