#include"Plotter.cc"
#ifndef __SKFLATPLOTTER_CC__
#define __SKFLATPLOTTER_CC__
class SKFlatPlotter:public Plotter{
public:
  SKFlatPlotter(TString mode_="",TString Analyzer_="");

  TString Analyzer;
  TString AnalyzerSuffix;
  TString SkimTree=".*";

  virtual int Setup(TString mode_,TString Analyzer_);
  virtual TString GetSetupStringForCondor();
  virtual void SetAnalyzer(TString Analyzer_);
  virtual void SetupSamples();
  virtual void SetupSystematics();
};
SKFlatPlotter::SKFlatPlotter(TString mode_,TString Analyzer_){
  Setup(mode_,Analyzer_);
}
void SKFlatPlotter::SetAnalyzer(TString Analyzer_){
  if(Analyzer_=="") return;
  int pos=Analyzer_.Index("_backup");
  if(pos<0) pos=Analyzer_.Length();
  Analyzer=Analyzer_(0,pos);
  AnalyzerSuffix=Analyzer_(pos,Analyzer_.Length());
  return;
}
void SKFlatPlotter::SetupSamples(){

  for(TString era:{"2016preVFP","2016postVFP","2017","2018"}){
    samples["muon"+era]=Sample("data (#mu#mu)","SAMPLE data "+era,kBlack,20)+TRegexp(era+"/DATA/"+Analyzer+SkimTree+"_DoubleMuon_[A-Z]")+TRegexp(era+"/DATA/"+Analyzer+SkimTree+"_SingleMuon_[A-Z]");
    samples["electron"+era]=Sample("data (ee)","SAMPLE data "+era,kBlack,20)+TRegexp(era+"/DATA/"+Analyzer+SkimTree+"_.*EG.*_[A-Z]")+TRegexp(era+"/DATA/"+Analyzer+SkimTree+"_SingleElectron_[A-Z]");
    samples["ww"+era]=Sample("WW","SAMPLE sim ww "+era,kBlue)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_WW_pythia$");
    samples["wz"+era]=Sample("WZ","SAMPLE sim wz "+era,kBlue)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_WZ_pythia$");
    samples["zz"+era]=Sample("ZZ","SAMPLE sim zz "+era,kBlue)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_ZZ_pythia$");
    samples["vv"+era]=Sample("Diboson","SUM",kBlue)+("ww"+era)+("wz"+era)+("zz"+era);
    samples["wjets"+era]=Sample("W","SAMPLE sim wjets "+era,kYellow)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_WJets_MG$");
    samples["ttll"+era]=Sample("t#bar{t}#rightarrowll","SAMPLE sim tt ttll "+era,kMagenta+1)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_TTLL_powheg$");
    samples["ttlj"+era]=Sample("t#bar{t}#rightarrowlj","SAMPLE sim tt ttlj "+era,kMagenta+2)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_TTLJ_powheg$");
    samples["ttjj"+era]=Sample("t#bar{t}#rightarrowjj","SAMPLE sim tt ttjj "+era,kMagenta+3)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_TTJJ_powheg$");
    samples["tw"+era]=Sample("tW","SAMPLE sim tw "+era,kMagenta+10)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_SingleTop_tW_.*top_NoFullyHad$");
    samples["stt"+era]=Sample("Single top tch","SAMPLE sim stt "+era,kMagenta+11)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_SingleTop_tch_.*$");
    samples["sts"+era]=Sample("Single top sch","SAMPLE sim sts "+era,kMagenta+12)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_SingleTop_sch_.*$");
    samples["st"+era]=Sample("Single top","SUM",kMagenta+10)+("tw"+era)+("stt"+era)+("sts"+era);
    samples["aa"+era]=Sample("#gamma#gamma#rightarrowll","SAMPLE sim aa "+era,kYellow+1)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_GGToLL$");

    samples["amc"+era]=Sample("#gamma*/Z#rightarrowll","SAMPLE sim dy "+era,kRed)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_DYJets$");
    samples["mi"+era]=Sample("#gamma*/Z#rightarrowll","SAMPLE sim dy "+era,kRed)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_DYJetsTo.*MiNNLO$");
    // for(auto& sub:samples["mi"].subs){
    //   if(sub.title.Contains("DYJetsToEE")&&sub.title.Contains("2017"))
    //     sub.weight=0.99;
    // }
    samples["mg"+era]=Sample("#gamma*/Z#rightarrowll","SAMPLE sim dy "+era,kRed)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_.*DYJets_MG$");
    samples["mg10"+era]=Sample("#gamma*/Z#rightarrowll","SAMPLE sim dy "+era,kRed)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_.*DYJets10to50_MG$");
    samples["amcJet"+era]=Sample("#gamma*/Z#rightarrowll","SAMPLE sim dy "+era,kRed)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_.*DY[0-9]Jets$");
    samples["amcPt"+era]=Sample("#gamma*/Z#rightarrowll","SAMPLE sim dy "+era,kRed)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_.*DYJets_Pt-[0-9]*To[0-9Inf]*$");
    samples["amcM"+era]=Sample("#gamma*/Z#rightarrowll","SAMPLE sim dy "+era,kRed)+TRegexp(era+"/.*"+Analyzer+SkimTree+"_.*DYJets_M-[0-9]*to[0-9Inf]*$");
  }

  samples["data"]=Sample("data","SUM data",kBlack,20)+"muon2016preVFP"+"muon2016postVFP"+"muon2017"+"muon2018"+"electron2016preVFP"+"electron2016postVFP"+"electron2017"+"electron2018";
  samples["vv"]=Sample("Diboson","SUM",kBlue)+"vv2016preVFP"+"vv2016postVFP"+"vv2017"+"vv2018";
  samples["wjets"]=Sample("W","SUM",kYellow)+"wjets2016preVFP"+"wjets2016postVFP"+"wjets2017"+"wjets2018";
  samples["ttll"]=Sample("t#bar{t}#rightarrowll","SUM",kMagenta+1)+"ttll2016preVFP"+"ttll2016postVFP"+"ttll2017"+"ttll2018";
  samples["ttlj"]=Sample("t#bar{t}#rightarrowlj","SUM",kMagenta+2)+"ttlj2016preVFP"+"ttlj2016postVFP"+"ttlj2017"+"ttlj2018";
  samples["ttjj"]=Sample("t#bar{t}#rightarrowjj","SUM",kMagenta+3)+"ttjj2016preVFP"+"ttjj2016postVFP"+"ttjj2017"+"ttjj2018";
  samples["tw"]=Sample("tW","SUM",kMagenta+10)+"tw2016preVFP"+"tw2016postVFP"+"tw2017"+"tw2018";
  samples["st"]=Sample("Single top","SUM",kMagenta+10)+"st2016preVFP"+"st2016postVFP"+"st2017"+"st2018";
  samples["aa"]=Sample("#gamma#gamma#rightarrowll","SUM",kYellow+1)+"aa2016preVFP"+"aa2016postVFP"+"aa2017"+"aa2018";
  
  samples["amc"]=Sample("#gamma*/Z#rightarrowll","SUM",kRed)+"amc2016preVFP"+"amc2016postVFP"+"amc2017"+"amc2018";
  samples["mi"]=Sample("#gamma*/Z#rightarrowll","SUM",kRed)+"mi2016preVFP"+"mi2016postVFP"+"mi2017"+"mi2018";
  // for(auto& sub:samples["mi"].subs){
  //   if(sub.title.Contains("DYJetsToEE")&&sub.title.Contains("2017"))
  //     sub.weight=0.99;
  // }
  samples["mg"]=Sample("#gamma*/Z#rightarrowll","SUM",kRed)+"mg2016preVFP"+"mg2016postVFP"+"mg2017"+"mg2018";
  samples["mg10"]=Sample("#gamma*/Z#rightarrowll","SUM",kRed)+"mg102016preVFP"+"mg102016postVFP"+"mg102017"+"mg102018";
  samples["amcJet"]=Sample("#gamma*/Z#rightarrowll","SUM",kRed)+"amcJet2016preVFP"+"amcJet2016postVFP"+"amcJet2017"+"amcJet2018";
  samples["amcPt"]=Sample("#gamma*/Z#rightarrowll","SUM",kRed)+"amcPt2016preVFP"+"amcPt2016postVFP"+"amcPt2017"+"amcPt2018";
  samples["amcM"]=Sample("#gamma*/Z#rightarrowll","SUM",kRed)+"amcM2016preVFP"+"amcM2016postVFP"+"amcM2017"+"amcM2018";

  samples["tt"]=Sample("t#bar{t}","SUM",kMagenta)+"ttll"+"ttlj"+"ttjj";
  samples["tttw"]=Sample("t#bar{t}, tW","SUM",kMagenta)+"tt"+"tw";
  samples["ttst"]=Sample("t#bar{t}, single top","SUM",kMagenta)+"tt"+"st";

  TString dysamples[]={"amc","amcJet","amcPt","amcM","mg","mg10","mi"};
  for(auto dysample:dysamples){
    samples["bx_"+dysample]="bx_"%(Sample("#gamma*/Z#rightarrowll (b init)","SUM",kRed-5)+dysample); //temp
    samples["tau_"+dysample]="tau_"%(Sample("#gamma*/Z#rightarrow#tau#tau","SUM dytau",kGreen)+dysample);
    samples["tau_"+dysample].RemoveTag("dy");
    samples["lhe_"+dysample]="lhe_"%(Sample("#gamma*/Z#rightarrowll (LHE)","SUM",kBlue)+dysample);
    samples["gen_"+dysample]="gen_"%(Sample("#gamma*/Z#rightarrowll (GEN)","SUM",kGreen)+dysample);
    samples["genfid_"+dysample]="genfid_"%(Sample("#gamma*/Z#rightarrowll (GEN fiducial)","SUM",kMagenta)+dysample);
    samples["truth_"+dysample]="truth_"%(Sample("#gamma*/Z#rightarrowll (truth)","SUM",kCyan)+dysample);
    samples["ss_"+dysample]="ss_"%(Sample("QCD multi-jet","SUM",kCyan)+"data"-dysample-("tau_"+dysample)-"vv"-"wjets"-"tt"-"st"-"aa");
    samples["fake_"+dysample]="fake_"%(Sample("QCD multi-jet","SUM",kOrange)+"data"-dysample-("tau_"+dysample)-"vv"-"wjets"-"tt"-"st"-"aa");
  }
  samples["ss"]=samples["ss_mi"];
  samples["amcPt_stack"]=Sample("DY Pt-binned","STACK",kBlue)+TRegexp("/"+Analyzer+SkimTree+"_.*DYJets_Pt-[0-9]*To[0-9Inf]*$");
  for(auto& sub:samples["amcPt_stack"].subs) sub.title=sub.title(TRegexp("Pt-[0-9]*To[0-9Inf]*"));
  samples["amcM_stack"]=Sample("DY M-binned","STACK",kBlue)+TRegexp("/"+Analyzer+SkimTree+"_.*DYJets_M-[0-9]*to[0-9Inf]*$");
  for(auto& sub:samples["amcM_stack"].subs) sub.title=sub.title(TRegexp("M-[0-9]*to[0-9Inf]*"));  

  samples["qcdss_ee"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[eE][eEl]&&!0bjet&&!nbjet qcdss_ee",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa"-"mg10")*1.011;
  samples["qcdss_ee_0bjet"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[eE][eEl]&&0bjet qcdss_ee_0bjet",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa"-"mg10")*1.010;
  samples["qcdss_ee_nbjet"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[eE][eEl]&&nbjet qcdss_ee_nbjet",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa"-"mg10")*1.018;
  samples["qcdss_mm"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[mM][mMu]&&!0bjet&&!nbjet qcdss_mm",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*2.276;
  samples["qcdss_mm_0bjet"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[mM][mMu]&&0bjet qcdss_mm_0bjet",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*2.304;
  samples["qcdss_mm_nbjet"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[mM][mMu]&&nbjet qcdss_mm_nbjet",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*1.158;
  samples["qcdss_em"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[eE][mM]&&!0bjet&&!nbjet qcdss_em",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*1.000;
  samples["qcdss_em_0bjet"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[eE][mM]&&0bjet qcdss_em_0bjet",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*1.000;
  samples["qcdss_em_nbjet"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[eE][mM]&&nbjet qcdss_em_nbjet",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*1.000;
  samples["qcdss_me"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[mM][eE]&&!0bjet&&!nbjet qcdss_me",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*1.000;
  samples["qcdss_me_0bjet"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[mM][eE]&&0bjet qcdss_me_0bjet",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*1.000;
  samples["qcdss_me_nbjet"]="ss_"%(Sample("QCD multi-jet (SS-method)","SUM filter:[mM][eE]&&nbjet qcdss_me_nbjet",kCyan)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa")*1.000;
  for(auto& [key,sample]:samples){
    if(!key.Contains("qcdss_")) continue;
    for(auto& sub:sample.subs){
      if(!sub.HasTag("data")) sub.AddTag("qcdss_prompt");
    }
  }

  samples["qcdss"]=Sample("QCD multi-jet","SUM",Style(kCyan),Style(kCyan,-1,3004,"e2"))+"qcdss_ee"+"qcdss_ee_0bjet"+"qcdss_ee_nbjet"+"qcdss_mm"+"qcdss_mm_0bjet"+"qcdss_mm_nbjet"+"qcdss_em"+"qcdss_em_0bjet"+"qcdss_em_nbjet"+"qcdss_me"+"qcdss_me_0bjet"+"qcdss_me_nbjet";

  samples["fake_mi"]="fake_"%(Sample("QCD multi-jet (TF method)","SUM qcdtf",Style(kOrange),Style(kOrange,-1,3005,"e2"))+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa");
  samples["qcdtf"]=samples["fake_mi"];
  samples["qcdtf"].title="QCD multi-jet";
  samples["qcd"]=samples["qcdtf"];
  samples["qcd"].alts["qcdss"]=samples["qcdss"];
  samples["fakecpt_mi"]="fakecpt_"%(Sample("QCD multi-jet (TF, cone pT)","SUM",kBlue)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa");
  samples["fakempt_mi"]="fakempt_"%(Sample("QCD multi-jet (TF, modified pT)","SUM",kGreen)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa");
  samples["fakelj_mi"]="fakelj_"%(Sample("QCD multi-jet (TF, lj)","SUM",kMagenta)+"data"-"mi"-"tau_mi"-"vv"-"wjets"-"ttst"-"aa");

  samples["zp"]=Sample("Z'","SAMPLE sim",kRed)+TRegexp("/"+Analyzer+SkimTree+"_ZPrime$");
  samples["zpsb"]=Sample("Z'","SAMPLE sim",kGreen+2)+TRegexp("/"+Analyzer+SkimTree+"_ZPrimeToMuMuSB$");
  samples["bbllpll"]=Sample("bbll (#eta_{LL})","SAMPLE sim",kBlue)+TRegexp("/"+Analyzer+SkimTree+"_bbll_M-[0-9]*To[0-9Inf]*_Lambda-10TeV_posEtaLL$");
  samples["bbllplr"]=Sample("bbll (#eta_{LR})","SAMPLE sim",kRed)+TRegexp("/"+Analyzer+SkimTree+"_bbll_M-[0-9]*To[0-9Inf]*_Lambda-10TeV_posEtaLR$");
  samples["bbllprl"]=Sample("bbll (#eta_{RL})","SAMPLE sim",kGreen+1)+TRegexp("/"+Analyzer+SkimTree+"_bbll_M-[0-9]*To[0-9Inf]*_Lambda-10TeV_posEtaRL$");
  samples["bbllprr"]=Sample("bbll (#eta_{RR})","SAMPLE sim",kCyan+1)+TRegexp("/"+Analyzer+SkimTree+"_bbll_M-[0-9]*To[0-9Inf]*_Lambda-10TeV_posEtaRR$");
}

int SKFlatPlotter::Setup(TString mode_,TString Analyzer_){
  Reset();
  SetAnalyzer(Analyzer_);
  if(Analyzer!="") ScanFiles((TString)getenv("SKFlatOutputDir")+getenv("SKFlatV")+"/"+Analyzer+AnalyzerSuffix+"/");
  SetupSamples();
  SetupEntries(mode_);
  SetupSystematics();

  if(Verbosity>VERBOSITY::WARNING) std::cout<<"[Setup] nentries: "<<entries.size()<<endl;
  if(Verbosity>VERBOSITY::WARNING) std::cout<<"[Setup] nsys: "<<systematics.size()<<endl;

  return 1;
}
TString SKFlatPlotter::GetSetupStringForCondor(){
  return "Setup\\(\\\\\\\""+mode+"\\\\\\\",\\\\\\\""+Analyzer+AnalyzerSuffix+"\\\\\\\"\\)";
}
void SKFlatPlotter::SetupSystematics(){
  if(Verbosity>VERBOSITY::WARNING) std::cout<<"[SetupSystematics]"<<endl;
  AddSystematic("PUweight","PU",Systematic::Type::ENVELOPE,"_PUweight_up _PUweight_down","sim");
  AddSystematic("prefireweight2016a","prefiring unc.",Systematic::Type::ENVELOPE,"_prefireweight_up _prefireweight_down","sim&&2016preVFP");
  AddSystematic("prefireweight2016b","prefiring unc.",Systematic::Type::ENVELOPE,"_prefireweight_up _prefireweight_down","sim&&2016postVFP");
  AddSystematic("prefireweight2017","prefiring unc.",Systematic::Type::ENVELOPE,"_prefireweight_up _prefireweight_down","sim&&2017");
  AddSystematic("prefireweight2018","prefiring unc.",Systematic::Type::ENVELOPE,"_prefireweight_up _prefireweight_down","sim&&2018");
  AddSystematic("prefireweight","prefiring unc.",Systematic::Type::MULTI,"prefireweight2016a prefireweight2016b prefireweight2017 prefireweight2018");
  AddSystematic("prefireweight_sys3","prefiring new3",Systematic::Type::ENVELOPE,"_newprefireweight3","sim");
  AddSystematic("prefireweight_sys4","prefiring new4",Systematic::Type::ENVELOPE,"_newprefireweight4","sim");
  AddSystematic("prefireweight_sys5","prefiring new5",Systematic::Type::ENVELOPE,"_newprefireweight5","sim");
  AddSystematic("prefireweight_sys6","prefiring new6",Systematic::Type::ENVELOPE,"_newprefireweight6","sim");
  AddSystematic("prefireweight_plus","prefiring unc.",Systematic::Type::MULTI,"prefireweight prefireweight_sys3 prefireweight_sys4 prefireweight_sys5 "); //prefireweight_sys6
  AddSystematic("z0weight","no z_{vtx} reweight",Systematic::Type::ENVELOPE,"_z0weight _noz0weight","sim");
  AddSystematic("CFSF2016a","charge-flip",Systematic::Type::ENVELOPE,"_CFSF_up _CFSF_down","sim&&2016preVFP");
  AddSystematic("CFSF2016b","charge-flip",Systematic::Type::ENVELOPE,"_CFSF_up _CFSF_down","sim&&2016postVFP");
  AddSystematic("CFSF2017","charge-flip",Systematic::Type::ENVELOPE,"_CFSF_up _CFSF_down","sim&&2017");
  AddSystematic("CFSF2018","charge-flip",Systematic::Type::ENVELOPE,"_CFSF_up _CFSF_down","sim&&2018");
  AddSystematic("CFSF","charge-flip",Systematic::Type::MULTI,"CFSF2016a CFSF2016b CFSF2017 CFSF2018");

  AddSystematic("btaghcorr","b tagging (heavy, era-correlated)",Systematic::Type::ENVELOPE,"_btagSF_hcorr","sim");
  AddSystematic("btaghuncorr2016a","b tagging (heavy, era-uncorrelated)",Systematic::Type::ENVELOPE,"_btagSF_huncorr","sim&&2016preVFP");
  AddSystematic("btaghuncorr2016b","b tagging (heavy, era-uncorrelated)",Systematic::Type::ENVELOPE,"_btagSF_huncorr","sim&&2016postVFP");
  AddSystematic("btaghuncorr2017","b tagging (heavy, era-uncorrelated)",Systematic::Type::ENVELOPE,"_btagSF_huncorr","sim&&2017");
  AddSystematic("btaghuncorr2018","b tagging (heavy, era-uncorrelated)",Systematic::Type::ENVELOPE,"_btagSF_huncorr","sim&&2018");
  AddSystematic("btaghuncorr","b tagging (heavy, era-uncorrelated)",Systematic::Type::MULTI,"btaghuncorr2016a btaghuncorr2016b btaghuncorr2017 btaghuncorr2018");
  AddSystematic("btagh","b tagging (heavy)",Systematic::Type::MULTI,"btaghcorr btaghuncorr");
  AddSystematic("btaglcorr","b tagging (light, era-correlated)",Systematic::Type::ENVELOPE,"_btagSF_lcorr","sim");
  AddSystematic("btagluncorr2016a","b tagging (light, era-uncorrelated)",Systematic::Type::ENVELOPE,"_btagSF_luncorr","sim&&2016preVFP");
  AddSystematic("btagluncorr2016b","b tagging (light, era-uncorrelated)",Systematic::Type::ENVELOPE,"_btagSF_luncorr","sim&&2016postVFP");
  AddSystematic("btagluncorr2017","b tagging (light, era-uncorrelated)",Systematic::Type::ENVELOPE,"_btagSF_luncorr","sim&&2017");
  AddSystematic("btagluncorr2018","b tagging (light, era-uncorrelated)",Systematic::Type::ENVELOPE,"_btagSF_luncorr","sim&&2018");
  AddSystematic("btagluncorr","b tagging (light, era-uncorrelated)",Systematic::Type::MULTI,"btagluncorr2016a btagluncorr2016b btagluncorr2017 btagluncorr2018");
  AddSystematic("btagl","b tagging (light)",Systematic::Type::MULTI,"btaglcorr btagluncorr");
  AddSystematic("btag","b tagging",Systematic::Type::MULTI,"btagh btagl");

  AddSystematic("bcharge","b charge determination",Systematic::Type::HESSIAN,"_bchargeSF_s0m0 _bchargeSF_s0m1","sim");

  AddSystematic("JES_data","JES (data)",Systematic::Type::ENVELOPE,"_jet_scale_up _jet_scale_down","data");
  AddSystematic("JES_sim","JES (sim.)",Systematic::Type::ENVELOPE,"_jet_scale_up _jet_scale_down","sim");
  AddSystematic("JES2016a","JES 2016a",Systematic::Type::ENVELOPE,"_jet_scale_up _jet_scale_down","sim&&2016preVFP");
  AddSystematic("JES2016b","JES 2016b",Systematic::Type::ENVELOPE,"_jet_scale_up _jet_scale_down","sim&&2016postVFP");
  AddSystematic("JES2017","JES 2017",Systematic::Type::ENVELOPE,"_jet_scale_up _jet_scale_down","sim&&2017");
  AddSystematic("JES2018","JES 2018",Systematic::Type::ENVELOPE,"_jet_scale_up _jet_scale_down","sim&&2018");
  AddSystematic("JER2016a","JER 2016a",Systematic::Type::ENVELOPE,"_jet_smear_up _jet_smear_down","sim&&2016preVFP");
  AddSystematic("JER2016b","JER 2016b",Systematic::Type::ENVELOPE,"_jet_smear_up _jet_smear_down","sim&&2016postVFP");
  AddSystematic("JER2017","JER 2017",Systematic::Type::ENVELOPE,"_jet_smear_up _jet_smear_down","sim&&2017");
  AddSystematic("JER2018","JER 2018",Systematic::Type::ENVELOPE,"_jet_smear_up _jet_smear_down","sim&&2018");
  AddSystematic("JES","JES",Systematic::Type::MULTI,"JES2016a JES2016b JES2017 JES2018");
  AddSystematic("JER","JER",Systematic::Type::MULTI,"JER2016a JER2016b JER2017 JER2018");
  AddSystematic("JEC","JEC",Systematic::Type::MULTI,"JES JER");
  
  int nreplica=20;
  AddSystematic("efficiencySF_stat","eff. stat.",Systematic::Type::GAUSSIAN,FormRange("_efficiencySF_stat%d",Range(nreplica)),"sim");
  AddSystematic("efficiencySF_e_sys1","eff. e sys1",Systematic::Type::CORRELATED,"_electronRECOSF_s1m0 _electronIDSF_s1m0 _triggerSF_s1m0","sim");
  AddSystematic("efficiencySF_e_sys2","eff. e sys2",Systematic::Type::CORRELATED,"_electronRECOSF_s2m0 _electronIDSF_s2m0 _triggerSF_s2m0","sim");
  AddSystematic("efficiencySF_e_sys3","eff. e sys3",Systematic::Type::CORRELATED,"_electronRECOSF_s3m0 _electronIDSF_s3m0 _triggerSF_s3m0","sim");
  AddSystematic("efficiencySF_e_sys4","eff. e sys4",Systematic::Type::CORRELATED,"_electronRECOSF_s4m0 _electronIDSF_s4m0 _triggerSF_s4m0","sim");
  AddSystematic("efficiencySF_e_sys5","eff. e sys5",Systematic::Type::CORRELATED,"_electronRECOSF_s5m0 _electronIDSF_s5m0 _triggerSF_s5m0","sim");
  AddSystematic("efficiencySF_e_sys6","eff. e sys6",Systematic::Type::CORRELATED,"_electronRECOSF_s6m0 _electronIDSF_s6m0 _triggerSF_s6m0","sim");
  AddSystematic("efficiencySF_e_s7m0","eff. e s7m0",Systematic::Type::CORRELATED,"_electronRECOSF_s7m0 _electronIDSF_s7m0 _triggerSF_s7m0","sim");
  AddSystematic("efficiencySF_e_s7m1","eff. e s7m1",Systematic::Type::CORRELATED,"_electronRECOSF_s7m1 _electronIDSF_s7m1 _triggerSF_s7m1","sim");
  AddSystematic("efficiencySF_e_sys7","eff. e sys7",Systematic::Type::MULTI,"efficiencySF_e_s7m0 efficiencySF_e_s7m1");
  AddSystematic("efficiencySF_e_s8m0","eff. e s8m0",Systematic::Type::CORRELATED,"_electronRECOSF_s8m0 _electronIDSF_s8m0 _triggerSF_s8m0","sim");
  AddSystematic("efficiencySF_e_s8m1","eff. e s8m1",Systematic::Type::CORRELATED,"_electronRECOSF_s8m1 _electronIDSF_s8m1 _triggerSF_s8m1","sim");
  AddSystematic("efficiencySF_e_sys8","eff. e sys8",Systematic::Type::MULTI,"efficiencySF_e_s8m0 efficiencySF_e_s8m1");
  AddSystematic("efficiencySF_e_sys9","eff. e sys9",Systematic::Type::CORRELATED,"_electronRECOSF_s9m0 _electronIDSF_s9m0 _triggerSF_s9m0","sim");
  AddSystematic("efficiencySF_e_sys10","eff. e sys10",Systematic::Type::CORRELATED,"_electronRECOSF_s10m0 _electronIDSF_s10m0 _triggerSF_s10m0","sim");
  AddSystematic("efficiencySF_e_s11m0","eff. e s11m0",Systematic::Type::CORRELATED,"_electronRECOSF_s11m0 _electronIDSF_s11m0 _triggerSF_s11m0","sim");
  AddSystematic("efficiencySF_e_s11m1","eff. e s11m1",Systematic::Type::CORRELATED,"_electronRECOSF_s11m1 _electronIDSF_s11m1 _triggerSF_s11m1","sim");
  AddSystematic("efficiencySF_e_sys11","eff. e sys11",Systematic::Type::MULTI,"efficiencySF_e_s11m0 efficiencySF_e_s11m1");
  AddSystematic("efficiencySF_e_s12m0","eff. e s12m0",Systematic::Type::CORRELATED,"_electronRECOSF_s12m0 _electronIDSF_s12m0 _triggerSF_s12m0","sim");
  AddSystematic("efficiencySF_e_s12m1","eff. e s12m1",Systematic::Type::CORRELATED,"_electronRECOSF_s12m1 _electronIDSF_s12m1 _triggerSF_s12m1","sim");
  AddSystematic("efficiencySF_e_sys12","eff. e sys12",Systematic::Type::MULTI,"efficiencySF_e_s12m0 efficiencySF_e_s12m1");
  AddSystematic("efficiencySF_e_s13m0","eff. e s13m0",Systematic::Type::CORRELATED,"_electronRECOSF_s13m0 _electronIDSF_s13m0 _triggerSF_s13m0","sim");
  AddSystematic("efficiencySF_e_s13m1","eff. e s13m1",Systematic::Type::CORRELATED,"_electronRECOSF_s13m1 _electronIDSF_s13m1 _triggerSF_s13m1","sim");
  AddSystematic("efficiencySF_e_sys13","eff. e sys13",Systematic::Type::MULTI,"efficiencySF_e_s13m0 efficiencySF_e_s13m1");
  AddSystematic("efficiencySF_e_sys14","eff. e sys14",Systematic::Type::CORRELATED,"_electronRECOSF_s14m0 _electronIDSF_s14m0 _triggerSF_s14m0","sim");
  AddSystematic("efficiencySF_e_sys15","eff. e sys15",Systematic::Type::CORRELATED,"_electronRECOSF_s15m0 _electronIDSF_s15m0 _triggerSF_s15m0","sim");
  AddSystematic("efficiencySF_e_sys16","eff. e sys16",Systematic::Type::CORRELATED,"_electronRECOSF_s16m0 _electronIDSF_s16m0 _triggerSF_s16m0","sim");
  AddSystematic("efficiencySF_e_sys17","eff. e sys17",Systematic::Type::CORRELATED,"_electronRECOSF_s17m0 _electronIDSF_s17m0 _triggerSF_s17m0","sim");
  AddSystematic("efficiencySF_e_residual","eff. e sys18",Systematic::Type::CORRELATED,"_electronIDSF_s18m0","sim"); //residual
  AddSystematic("efficiencySF_e_noresidual","eff. e",Systematic::Type::MULTI,FormRange("efficiencySF_e_sys%d",Range(1,18)));
  AddSystematic("efficiencySF_e","eff. e",Systematic::Type::MULTI,"efficiencySF_e_noresidual efficiencySF_e_residual");

  AddSystematic("efficiencySF_m_sys1","eff. m sys1",Systematic::Type::CORRELATED,"_muonTrackingSF_s1m0 _muonRECOSF_s1m0 _muonIDSF_s1m0 _triggerSF_s1m0","sim");
  AddSystematic("efficiencySF_m_sys2","eff. m sys2",Systematic::Type::CORRELATED,"_muonTrackingSF_s2m0 _muonRECOSF_s2m0 _muonIDSF_s2m0 _triggerSF_s2m0","sim");
  AddSystematic("efficiencySF_m_sys3","eff. m sys3",Systematic::Type::CORRELATED,"_muonTrackingSF_s3m0 _muonRECOSF_s3m0 _muonIDSF_s3m0 _triggerSF_s3m0","sim");
  AddSystematic("efficiencySF_m_sys4","eff. m sys4",Systematic::Type::CORRELATED,"_muonTrackingSF_s4m0 _muonRECOSF_s4m0 _muonIDSF_s4m0 _triggerSF_s4m0","sim");
  AddSystematic("efficiencySF_m_sys5","eff. m sys5",Systematic::Type::CORRELATED,"_muonTrackingSF_s5m0 _muonRECOSF_s5m0 _muonIDSF_s5m0 _triggerSF_s5m0","sim");
  AddSystematic("efficiencySF_m_sys6","eff. m sys6",Systematic::Type::CORRELATED,"_muonTrackingSF_s6m0 _muonRECOSF_s6m0 _muonIDSF_s6m0 _triggerSF_s6m0","sim");
  AddSystematic("efficiencySF_m_s7m0","eff. m s7m0",Systematic::Type::CORRELATED,"_muonTrackingSF_s7m0 _muonRECOSF_s7m0 _muonIDSF_s7m0 _triggerSF_s7m0","sim");
  AddSystematic("efficiencySF_m_s7m1","eff. m s7m1",Systematic::Type::CORRELATED,"_muonTrackingSF_s7m1 _muonRECOSF_s7m1 _muonIDSF_s7m1 _triggerSF_s7m1","sim");
  AddSystematic("efficiencySF_m_sys7","eff. m sys7",Systematic::Type::MULTI,"efficiencySF_m_s7m0 efficiencySF_m_s7m1");
  AddSystematic("efficiencySF_m_s8m0","eff. m s8m0",Systematic::Type::CORRELATED,"_muonTrackingSF_s8m0 _muonRECOSF_s8m0 _muonIDSF_s8m0 _triggerSF_s8m0","sim");
  AddSystematic("efficiencySF_m_s8m1","eff. m s8m1",Systematic::Type::CORRELATED,"_muonTrackingSF_s8m1 _muonRECOSF_s8m1 _muonIDSF_s8m1 _triggerSF_s8m1","sim");
  AddSystematic("efficiencySF_m_sys8","eff. m sys8",Systematic::Type::MULTI,"efficiencySF_m_s8m0 efficiencySF_m_s8m1");
  AddSystematic("efficiencySF_m_sys9","eff. m sys9",Systematic::Type::CORRELATED,"_muonTrackingSF_s9m0 _muonRECOSF_s9m0 _muonIDSF_s9m0 _triggerSF_s9m0","sim");
  AddSystematic("efficiencySF_m_sys10","eff. m sys10",Systematic::Type::CORRELATED,"_muonTrackingSF_s10m0 _muonRECOSF_s10m0 _muonIDSF_s10m0 _triggerSF_s10m0","sim");
  AddSystematic("efficiencySF_m_s11m0","eff. m s11m0",Systematic::Type::CORRELATED,"_muonTrackingSF_s11m0 _muonRECOSF_s11m0 _muonIDSF_s11m0 _triggerSF_s11m0","sim");
  AddSystematic("efficiencySF_m_s11m1","eff. m s11m1",Systematic::Type::CORRELATED,"_muonTrackingSF_s11m1 _muonRECOSF_s11m1 _muonIDSF_s11m1 _triggerSF_s11m1","sim");
  AddSystematic("efficiencySF_m_sys11","eff. m sys11",Systematic::Type::MULTI,"efficiencySF_m_s11m0 efficiencySF_m_s11m1");
  AddSystematic("efficiencySF_m_s12m0","eff. m s12m0",Systematic::Type::CORRELATED,"_muonTrackingSF_s12m0 _muonRECOSF_s12m0 _muonIDSF_s12m0 _triggerSF_s12m0","sim");
  AddSystematic("efficiencySF_m_s12m1","eff. m s12m1",Systematic::Type::CORRELATED,"_muonTrackingSF_s12m1 _muonRECOSF_s12m1 _muonIDSF_s12m1 _triggerSF_s12m1","sim");
  AddSystematic("efficiencySF_m_sys12","eff. m sys12",Systematic::Type::MULTI,"efficiencySF_m_s12m0 efficiencySF_m_s12m1");
  AddSystematic("efficiencySF_m_s13m0","eff. m s13m0",Systematic::Type::CORRELATED,"_muonTrackingSF_s13m0 _muonRECOSF_s13m0 _muonIDSF_s13m0 _triggerSF_s13m0","sim");
  AddSystematic("efficiencySF_m_s13m1","eff. m s13m1",Systematic::Type::CORRELATED,"_muonTrackingSF_s13m1 _muonRECOSF_s13m1 _muonIDSF_s13m1 _triggerSF_s13m1","sim");
  AddSystematic("efficiencySF_m_sys13","eff. m sys13",Systematic::Type::MULTI,"efficiencySF_m_s13m0 efficiencySF_m_s13m1");
  AddSystematic("efficiencySF_m_sys14","eff. m sys14",Systematic::Type::CORRELATED,"_muonTrackingSF_s14m0 _muonRECOSF_s14m0 _muonIDSF_s14m0 _triggerSF_s14m0","sim");
  AddSystematic("efficiencySF_m_sys15","eff. m sys15",Systematic::Type::CORRELATED,"_muonTrackingSF_s15m0 _muonRECOSF_s15m0 _muonIDSF_s15m0 _triggerSF_s15m0","sim");
  AddSystematic("efficiencySF_m_sys16","eff. m sys16",Systematic::Type::CORRELATED,"_muonTrackingSF_s16m0 _muonRECOSF_s16m0 _muonIDSF_s16m0 _triggerSF_s16m0","sim");
  AddSystematic("efficiencySF_m_residual","eff. m sys17",Systematic::Type::CORRELATED,"_muonIDSF_s17m0","sim"); //residual
  AddSystematic("efficiencySF_m_noresidual","eff. m (no residual)",Systematic::Type::MULTI,FormRange("efficiencySF_m_sys%d",Range(1,16)));
  AddSystematic("efficiencySF_m","eff. m",Systematic::Type::MULTI,"efficiencySF_m_noresidual efficiencySF_m_residual");

  // old
  AddSystematic("electronRECOSF_sys1","eff. e RECO sys1",Systematic::Type::ENVELOPE,"_electronRECOSF_s1m0","sim");
  AddSystematic("electronRECOSF_sys2","eff. e RECO sys2",Systematic::Type::ENVELOPE,"_electronRECOSF_s2m0","sim");
  AddSystematic("electronRECOSF_sys3","eff. e RECO sys3",Systematic::Type::ENVELOPE,"_electronRECOSF_s3m0","sim");
  AddSystematic("electronRECOSF_sys4","eff. e RECO sys4",Systematic::Type::ENVELOPE,"_electronRECOSF_s4m0","sim");
  AddSystematic("electronRECOSF_sys5","eff. e RECO sys5",Systematic::Type::ENVELOPE,"_electronRECOSF_s5m0","sim");
  AddSystematic("electronRECOSF_sys6","eff. e RECO sys6",Systematic::Type::ENVELOPE,"_electronRECOSF_s6m0","sim");
  AddSystematic("electronRECOSF_sys7","eff. e RECO sys7",Systematic::Type::ENVELOPE,"_electronRECOSF_s7m0 _electronRECOSF_s7m1","sim");
  AddSystematic("electronRECOSF_sys8","eff. e RECO sys8",Systematic::Type::ENVELOPE,"_electronRECOSF_s8m0 _electronRECOSF_s8m1","sim"); 
  AddSystematic("electronRECOSF_sys9","eff. e RECO sys9",Systematic::Type::ENVELOPE,"_electronRECOSF_s9m0","sim"); 
  AddSystematic("electronRECOSF_sys10","eff. e RECO sys10",Systematic::Type::ENVELOPE,"_electronRECOSF_s10m0","sim");
  AddSystematic("electronRECOSF_sys11","eff. e RECO sys11",Systematic::Type::ENVELOPE,"_electronRECOSF_s11m0 _electronRECOSF_s11m1","sim");
  AddSystematic("electronRECOSF_sys12","eff. e RECO sys12",Systematic::Type::ENVELOPE,"_electronRECOSF_s12m0 _electronRECOSF_s12m1","sim");
  AddSystematic("electronRECOSF_sys13","eff. e RECO sys13",Systematic::Type::ENVELOPE,"_electronRECOSF_s13m0 _electronRECOSF_s13m1","sim");
  AddSystematic("electronRECOSF_sys14","eff. e RECO sys14",Systematic::Type::ENVELOPE,"_electronRECOSF_s14m0","sim");
  AddSystematic("electronRECOSF_sys15","eff. e RECO sys15",Systematic::Type::ENVELOPE,"_electronRECOSF_s15m0","sim");
  AddSystematic("electronRECOSF_sys16","eff. e RECO sys16",Systematic::Type::ENVELOPE,"_electronRECOSF_s16m0","sim");
  AddSystematic("electronRECOSF","eff. e RECO syst.",Systematic::Type::MULTI,FormRange("electronRECOSF_sys%d",Range(1,17)),"sim");
  AddSystematic("electronIDSF_sys1","eff. e ID sys1",Systematic::Type::ENVELOPE,"_electronIDSF_s1m0","sim");
  AddSystematic("electronIDSF_sys2","eff. e ID sys2",Systematic::Type::ENVELOPE,"_electronIDSF_s2m0","sim");
  AddSystematic("electronIDSF_sys3","eff. e ID sys3",Systematic::Type::ENVELOPE,"_electronIDSF_s3m0","sim");
  AddSystematic("electronIDSF_sys4","eff. e ID sys4",Systematic::Type::ENVELOPE,"_electronIDSF_s4m0","sim");
  AddSystematic("electronIDSF_sys5","eff. e ID sys5",Systematic::Type::ENVELOPE,"_electronIDSF_s5m0","sim");
  AddSystematic("electronIDSF_sys6","eff. e ID sys6",Systematic::Type::ENVELOPE,"_electronIDSF_s6m0","sim");
  AddSystematic("electronIDSF_sys7","eff. e ID sys7",Systematic::Type::ENVELOPE,"_electronIDSF_s7m0 _electronIDSF_s7m1","sim");
  AddSystematic("electronIDSF_sys8","eff. e ID sys8",Systematic::Type::ENVELOPE,"_electronIDSF_s8m0 _electronIDSF_s8m1","sim"); 
  AddSystematic("electronIDSF_sys9","eff. e ID sys9",Systematic::Type::ENVELOPE,"_electronIDSF_s9m0","sim"); 
  AddSystematic("electronIDSF_sys10","eff. e ID sys10",Systematic::Type::ENVELOPE,"_electronIDSF_s10m0","sim");
  AddSystematic("electronIDSF_sys11","eff. e ID sys11",Systematic::Type::ENVELOPE,"_electronIDSF_s11m0 _electronIDSF_s11m1","sim");
  AddSystematic("electronIDSF_sys12","eff. e ID sys12",Systematic::Type::ENVELOPE,"_electronIDSF_s12m0 _electronIDSF_s12m1","sim");
  AddSystematic("electronIDSF_sys13","eff. e ID sys13",Systematic::Type::ENVELOPE,"_electronIDSF_s13m0 _electronIDSF_s13m1","sim");
  AddSystematic("electronIDSF_sys14","eff. e ID sys14",Systematic::Type::ENVELOPE,"_electronIDSF_s14m0","sim");
  AddSystematic("electronIDSF_sys15","eff. e ID sys15",Systematic::Type::ENVELOPE,"_electronIDSF_s15m0","sim");
  AddSystematic("electronIDSF_sys16","eff. e ID sys16",Systematic::Type::ENVELOPE,"_electronIDSF_s16m0","sim");
  AddSystematic("electronIDSF_sys17","eff. e ID sys17",Systematic::Type::ENVELOPE,"_electronIDSF_s17m0","sim");
  AddSystematic("electronIDSF_sys18","eff. e ID sys18",Systematic::Type::ENVELOPE,"_electronIDSF_s18m0","sim"); //residual
  AddSystematic("electronIDSF","eff. e ID syst.",Systematic::Type::MULTI,FormRange("electronIDSF_sys%d",Range(1,18)),"sim");
  AddSystematic("muonTrackingSF_sys1","eff. #mu Trk sys1",Systematic::Type::ENVELOPE,"_muonTrackingSF_s1m0","sim");
  AddSystematic("muonTrackingSF_sys2","eff. #mu Trk sys2",Systematic::Type::ENVELOPE,"_muonTrackingSF_s2m0","sim");
  AddSystematic("muonTrackingSF_sys3","eff. #mu Trk sys3",Systematic::Type::ENVELOPE,"_muonTrackingSF_s3m0","sim");
  AddSystematic("muonTrackingSF_sys4","eff. #mu Trk sys4",Systematic::Type::ENVELOPE,"_muonTrackingSF_s4m0","sim");
  AddSystematic("muonTrackingSF_sys5","eff. #mu Trk sys5",Systematic::Type::ENVELOPE,"_muonTrackingSF_s5m0","sim");
  AddSystematic("muonTrackingSF_sys6","eff. #mu Trk sys6",Systematic::Type::ENVELOPE,"_muonTrackingSF_s6m0","sim");
  AddSystematic("muonTrackingSF_sys7","eff. #mu Trk sys7",Systematic::Type::ENVELOPE,"_muonTrackingSF_s7m0 _muonTrackingSF_s7m1","sim");
  AddSystematic("muonTrackingSF_sys8","eff. #mu Trk sys8",Systematic::Type::ENVELOPE,"_muonTrackingSF_s8m0 _muonTrackingSF_s8m1","sim");
  AddSystematic("muonTrackingSF_sys9","eff. #mu Trk sys9",Systematic::Type::ENVELOPE,"_muonTrackingSF_s9m0","sim");
  AddSystematic("muonTrackingSF_sys10","eff. #mu Trk sys10",Systematic::Type::ENVELOPE,"_muonTrackingSF_s10m0","sim");
  AddSystematic("muonTrackingSF_sys11","eff. #mu Trk sys11",Systematic::Type::ENVELOPE,"_muonTrackingSF_s11m0 _muonTrackingSF_s11m1","sim");
  AddSystematic("muonTrackingSF_sys12","eff. #mu Trk sys12",Systematic::Type::ENVELOPE,"_muonTrackingSF_s12m0 _muonTrackingSF_s12m1","sim");
  AddSystematic("muonTrackingSF_sys13","eff. #mu Trk sys13",Systematic::Type::ENVELOPE,"_muonTrackingSF_s13m0 _muonTrackingSF_s13m1","sim");
  AddSystematic("muonTrackingSF_sys14","eff. #mu Trk sys14",Systematic::Type::ENVELOPE,"_muonTrackingSF_s14m0","sim");
  AddSystematic("muonTrackingSF_sys15","eff. #mu Trk sys15",Systematic::Type::ENVELOPE,"_muonTrackingSF_s15m0","sim");
  AddSystematic("muonTrackingSF_sys16","eff. #mu Trk sys16",Systematic::Type::ENVELOPE,"_muonTrackingSF_s16m0","sim"); //altfactoring
  AddSystematic("muonTrackingSF","eff. #mu Trk syst.",Systematic::Type::MULTI,FormRange("muonTrackingSF_sys%d",Range(1,16)),"sim");
  AddSystematic("muonRECOSF_sys1","eff. #mu RECO sys1",Systematic::Type::ENVELOPE,"_muonRECOSF_s1m0","sim");
  AddSystematic("muonRECOSF_sys2","eff. #mu RECO sys2",Systematic::Type::ENVELOPE,"_muonRECOSF_s2m0","sim");
  AddSystematic("muonRECOSF_sys3","eff. #mu RECO sys3",Systematic::Type::ENVELOPE,"_muonRECOSF_s3m0","sim");
  AddSystematic("muonRECOSF_sys4","eff. #mu RECO sys4",Systematic::Type::ENVELOPE,"_muonRECOSF_s4m0","sim");
  AddSystematic("muonRECOSF_sys5","eff. #mu RECO sys5",Systematic::Type::ENVELOPE,"_muonRECOSF_s5m0","sim");
  AddSystematic("muonRECOSF_sys6","eff. #mu RECO sys6",Systematic::Type::ENVELOPE,"_muonRECOSF_s6m0","sim");
  AddSystematic("muonRECOSF_sys7","eff. #mu RECO sys7",Systematic::Type::ENVELOPE,"_muonRECOSF_s7m0 _muonRECOSF_s7m1","sim");
  AddSystematic("muonRECOSF_sys8","eff. #mu RECO sys8",Systematic::Type::ENVELOPE,"_muonRECOSF_s8m0","sim");
  AddSystematic("muonRECOSF_sys9","eff. #mu RECO sys9",Systematic::Type::ENVELOPE,"_muonRECOSF_s9m0","sim");
  AddSystematic("muonRECOSF_sys10","eff. #mu RECO sys10",Systematic::Type::ENVELOPE,"_muonRECOSF_s10m0","sim");
  AddSystematic("muonRECOSF_sys11","eff. #mu RECO sys11",Systematic::Type::ENVELOPE,"_muonRECOSF_s11m0 _muonRECOSF_s11m1","sim");
  AddSystematic("muonRECOSF_sys12","eff. #mu RECO sys12",Systematic::Type::ENVELOPE,"_muonRECOSF_s12m0 _muonRECOSF_s12m1","sim");
  AddSystematic("muonRECOSF_sys13","eff. #mu RECO sys13",Systematic::Type::ENVELOPE,"_muonRECOSF_s13m0 _muonRECOSF_s13m1","sim");
  AddSystematic("muonRECOSF_sys14","eff. #mu RECO sys14",Systematic::Type::ENVELOPE,"_muonRECOSF_s14m0","sim");
  AddSystematic("muonRECOSF_sys15","eff. #mu RECO sys15",Systematic::Type::ENVELOPE,"_muonRECOSF_s15m0","sim");
  AddSystematic("muonRECOSF_sys16","eff. #mu RECO sys16",Systematic::Type::ENVELOPE,"_muonRECOSF_s16m0","sim"); //altfactoring
  AddSystematic("muonRECOSF","eff. #mu RECO syst.",Systematic::Type::MULTI,FormRange("muonRECOSF_sys%d",Range(1,16)),"sim");
  AddSystematic("muonIDSF_sys1","eff. #mu ID sys1",Systematic::Type::ENVELOPE,"_muonIDSF_s1m0","sim");
  AddSystematic("muonIDSF_sys2","eff. #mu ID sys2",Systematic::Type::ENVELOPE,"_muonIDSF_s2m0","sim");
  AddSystematic("muonIDSF_sys3","eff. #mu ID sys3",Systematic::Type::ENVELOPE,"_muonIDSF_s3m0","sim");
  AddSystematic("muonIDSF_sys4","eff. #mu ID sys4",Systematic::Type::ENVELOPE,"_muonIDSF_s4m0","sim");
  AddSystematic("muonIDSF_sys5","eff. #mu ID sys5",Systematic::Type::ENVELOPE,"_muonIDSF_s5m0","sim");
  AddSystematic("muonIDSF_sys6","eff. #mu ID sys6",Systematic::Type::ENVELOPE,"_muonIDSF_s6m0","sim");
  AddSystematic("muonIDSF_sys7","eff. #mu ID sys7",Systematic::Type::ENVELOPE,"_muonIDSF_s7m0 _muonIDSF_s7m1","sim");
  AddSystematic("muonIDSF_sys8","eff. #mu ID sys8",Systematic::Type::ENVELOPE,"_muonIDSF_s8m0 _muonIDSF_s8m1","sim");
  AddSystematic("muonIDSF_sys9","eff. #mu ID sys9",Systematic::Type::ENVELOPE,"_muonIDSF_s9m0","sim");
  AddSystematic("muonIDSF_sys10","eff. #mu ID sys10",Systematic::Type::ENVELOPE,"_muonIDSF_s10m0","sim");
  AddSystematic("muonIDSF_sys11","eff. #mu ID sys11",Systematic::Type::ENVELOPE,"_muonIDSF_s11m0 _muonIDSF_s11m1","sim");
  AddSystematic("muonIDSF_sys12","eff. #mu ID sys12",Systematic::Type::ENVELOPE,"_muonIDSF_s12m0 _muonIDSF_s12m1","sim");
  AddSystematic("muonIDSF_sys13","eff. #mu ID sys13",Systematic::Type::ENVELOPE,"_muonIDSF_s13m0 _muonIDSF_s13m1","sim");
  AddSystematic("muonIDSF_sys14","eff. #mu ID sys14",Systematic::Type::ENVELOPE,"_muonIDSF_s14m0","sim");
  AddSystematic("muonIDSF_sys15","eff. #mu ID sys15",Systematic::Type::ENVELOPE,"_muonIDSF_s15m0","sim");
  AddSystematic("muonIDSF_sys16","eff. #mu ID sys16",Systematic::Type::ENVELOPE,"_muonIDSF_s16m0","sim"); //altfactoring
  AddSystematic("muonIDSF_sys17","eff. #mu ID sys17",Systematic::Type::ENVELOPE,"_muonIDSF_s17m0","sim"); //residual
  AddSystematic("muonIDSF","eff. #mu ID syst.",Systematic::Type::MULTI,FormRange("muonIDSF_sys%d",Range(1,16)),"sim");
  AddSystematic("triggerSF_sys1","eff. trig. sys1",Systematic::Type::ENVELOPE,"_triggerSF_s1m0","sim");
  AddSystematic("triggerSF_sys2","eff. trig. sys2",Systematic::Type::ENVELOPE,"_triggerSF_s2m0","sim");
  AddSystematic("triggerSF_sys3","eff. trig. sys3",Systematic::Type::ENVELOPE,"_triggerSF_s3m0","sim");
  AddSystematic("triggerSF_sys4","eff. trig. sys4",Systematic::Type::ENVELOPE,"_triggerSF_s4m0","sim");
  AddSystematic("triggerSF_sys5","eff. trig. sys5",Systematic::Type::ENVELOPE,"_triggerSF_s5m0","sim");
  AddSystematic("triggerSF_sys6","eff. trig. sys6",Systematic::Type::ENVELOPE,"_triggerSF_s6m0","sim");
  AddSystematic("triggerSF_sys7","eff. trig. sys7",Systematic::Type::ENVELOPE,"_triggerSF_s7m0 _triggerSF_s7m1","sim");
  AddSystematic("triggerSF_sys8","eff. trig. sys8",Systematic::Type::ENVELOPE,"_triggerSF_s8m0 _triggerSF_s8m1","sim"); 
  AddSystematic("triggerSF_sys9","eff. trig. sys9",Systematic::Type::ENVELOPE,"_triggerSF_s9m0","sim"); 
  AddSystematic("triggerSF_sys10","eff. trig. sys10",Systematic::Type::ENVELOPE,"_triggerSF_s10m0","sim");
  AddSystematic("triggerSF_sys11","eff. trig. sys11",Systematic::Type::ENVELOPE,"_triggerSF_s11m0 _triggerSF_s11m1","sim");
  AddSystematic("triggerSF_sys12","eff. trig. sys12",Systematic::Type::ENVELOPE,"_triggerSF_s12m0 _triggerSF_s12m1","sim");
  AddSystematic("triggerSF_sys13","eff. trig. sys13",Systematic::Type::ENVELOPE,"_triggerSF_s13m0 _triggerSF_s13m1","sim");
  AddSystematic("triggerSF_sys14","eff. trig. sys14",Systematic::Type::ENVELOPE,"_triggerSF_s14m0","sim");
  AddSystematic("triggerSF_sys15","eff. trig. sys15",Systematic::Type::ENVELOPE,"_triggerSF_s15m0","sim");
  AddSystematic("triggerSF_sys16","eff. trig. sys16",Systematic::Type::ENVELOPE,"_triggerSF_s16m0","sim");
  AddSystematic("triggerSF_sys17","eff. trig. sys17",Systematic::Type::ENVELOPE,"_triggerSF_s17m0","sim");
  AddSystematic("triggerSF_mode1","eff. trig. mode1",Systematic::Type::ENVELOPE,"_triggerSF_mode1","sim");
  AddSystematic("triggerSF_interpolation","eff. trig. interpolation",Systematic::Type::ENVELOPE,"_triggerSF_interpolation","sim");
  AddSystematic("triggerSF","eff. trig. syst.",Systematic::Type::MULTI,Join(" ",FormRange("triggerSF_sys%d",Range(1,18)))+" triggerSF_interpolation","sim");

  AddSystematic("noRECOSF","noRECOSF",Systematic::Type::ENVELOPE,"_noRECOSF","sim");
  AddSystematic("noIDSF","noIDSF",Systematic::Type::ENVELOPE,"_noIDSF","sim");
  AddSystematic("noISOSF","noISOSF",Systematic::Type::ENVELOPE,"_noISOSF","sim");
  AddSystematic("notriggerSF","notriggerSF",Systematic::Type::ENVELOPE,"_notriggerSF","sim");
  AddSystematic("noefficiencySF","noefficiencySF",Systematic::Type::ENVELOPE,"_noefficiencySF","sim");

  // AddSystematic("efficiencySF_residual","eff. residual",Systematic::Type::MULTI,"electronIDSF_sys18 muonIDSF_sys17","sim");
  // AddSystematic("efficiencySF","eff. unc.",Systematic::Type::MULTI,"efficiencySF_stat electronRECOSF electronIDSF muonTrackingSF muonRECOSF muonIDSF triggerSF efficiencySF_residual");
  // AddSystematic("efficiencySF_noresidual","eff. unc.",Systematic::Type::MULTI,"efficiencySF_stat electronRECOSF electronIDSF muonTrackingSF muonRECOSF muonIDSF triggerSF");

  AddSystematic("efficiencySF_residual","eff. residual",Systematic::Type::MULTI,"efficiencySF_e_residual efficiencySF_m_residual");
  AddSystematic("efficiencySF","eff. unc.",Systematic::Type::MULTI,"efficiencySF_stat efficiencySF_e efficiencySF_m");
  AddSystematic("efficiencySF_noresidual","eff. unc.",Systematic::Type::MULTI,"efficiencySF_stat efficiencySF_e_noresidual efficiencySF_m_noresidual");

  AddSystematic("effAN","systematic unc.",Systematic::Type::MULTI,"efficiencySF_noresidual z0weight");
  // AddSystematic("effAN2","systematic unc.",Systematic::Type::MULTI,"efficiencySF_stat electronRECOSF electronIDSF muonTrackingSF muonRECOSF muonIDSF triggerSF z0weight prefireweight PUweight zptweight dyscale dypdf dyalphaS qcdss");
  // AddSystematic("effAN2pp","systematic unc.",Systematic::Type::MULTI,"efficiencySF_stat electronRECOSF electronIDSF muonTrackingSF muonRECOSF muonIDSF triggerSF z0weight prefireweight_plus PUweight zptweight dyscale dypdf dyalphaS qcdss");
  // AddSystematic("effAN3","systematic unc.",Systematic::Type::MULTI,"efficiencySF_stat electronRECOSF electronIDSF muonTrackingSF muonRECOSF muonIDSF triggerSF z0weight prefireweight PUweight zptweight dyscale dypdf dyalphaS qcdss");
  // AddSystematic("efftest","efftest",Systematic::Type::MULTI,"efficiencySF_stat "+Join(" ",FormRange("electronRECOSF_sys%d",Range(1,13)))+" "+Join(" ",FormRange("electronIDSF_sys%d",Range(1,15)))+" "+Join(" ",FormRange("triggerSF_sys%d",Range(1,14)))+" z0weight prefireweight PUweight ");
  // AddSystematic("efftest_old","efftest_old",Systematic::Type::MULTI,"efficiencySF_stat "+Join(" ",FormRange("electronRECOSF_sys%d",Range(1,11)))+" "+Join(" ",FormRange("electronIDSF_sys%d",Range(1,12)))+" "+Join(" ",FormRange("triggerSF_sys%d",Range(1,11)))+" z0weight prefireweight PUweight ");
  
  AddSystematic("muonmomentum_stat","Roch. cor. stat.",Systematic::Type::GAUSSIAN,FormRange("_muonmomentum_s1m%d",Range(40)));
  AddSystematic("muonmomentum_sys2","Roch. cor. sys2",Systematic::Type::ENVELOPE,"_muonmomentum_s2m0");
  AddSystematic("muonmomentum_sys3","Roch. cor. sys3",Systematic::Type::ENVELOPE,"_muonmomentum_s3m0");
  AddSystematic("muonmomentum_sys4","Roch. cor. sys4",Systematic::Type::ENVELOPE,"_muonmomentum_s4m0");
  AddSystematic("muonmomentum_sys5","Roch. cor. sys5",Systematic::Type::ENVELOPE,"_muonmomentum_s5m0");
  AddSystematic("muonmomentum_residual","Roch. cor. residual",Systematic::Type::ENVELOPE,"_muonmomentum_residual","2016preVFP");
  AddSystematic("muonmomentum","Roch. cor.",Systematic::Type::MULTI,"muonmomentum_stat muonmomentum_sys2 muonmomentum_sys3 muonmomentum_sys4 muonmomentum_sys5 muonmomentum_residual");
  AddSystematic("muonmomentum_noresidual","Roch. cor.",Systematic::Type::MULTI,"muonmomentum_stat muonmomentum_sys2 muonmomentum_sys3 muonmomentum_sys4 muonmomentum_sys5");

  for(TString era:{"2016preVFP","2016postVFP","2017","2018"}){
    AddSystematic("muonmomentum_sys2_"+era,"Roch. cor. sys2",Systematic::Type::ENVELOPE,"_muonmomentum_s2m0",era);
    AddSystematic("muonmomentum_sys3_"+era,"Roch. cor. sys3",Systematic::Type::ENVELOPE,"_muonmomentum_s3m0",era);
    AddSystematic("muonmomentum_sys4_"+era,"Roch. cor. sys4",Systematic::Type::ENVELOPE,"_muonmomentum_s4m0",era);
    AddSystematic("muonmomentum_sys5_"+era,"Roch. cor. sys5",Systematic::Type::ENVELOPE,"_muonmomentum_s5m0",era);
    AddSystematic("muonmomentum_residual_"+era,"Roch. cor. residual",Systematic::Type::ENVELOPE,"_muonmomentum_residual",era);
  }
  AddSystematic("muonmomentum_era","Roch. cor.",Systematic::Type::MULTI,"muonmomentum_stat muonmomentum_sys2_2016preVFP muonmomentum_sys3_2016preVFP muonmomentum_sys4_2016preVFP muonmomentum_sys5_2016preVFP muonmomentum_residual_2016preVFP muonmomentum_sys2_2016postVFP muonmomentum_sys3_2016postVFP muonmomentum_sys4_2016postVFP muonmomentum_sys5_2016postVFP muonmomentum_residual_2016postVFP muonmomentum_sys2_2017 muonmomentum_sys3_2017 muonmomentum_sys4_2017 muonmomentum_sys5_2017 muonmomentum_residual_2017 muonmomentum_sys2_2018 muonmomentum_sys3_2018 muonmomentum_sys4_2018 muonmomentum_sys5_2018 muonmomentum_residual_2018");  

  AddSystematic("electronenergy_stat","Roch. cor. stat.",Systematic::Type::GAUSSIAN,FormRange("_electronenergy_s1m%d",Range(40)));
  AddSystematic("electronenergy_sys2","Roch. cor. sys2",Systematic::Type::ENVELOPE,"_electronenergy_s2m0");
  AddSystematic("electronenergy_sys3","Roch. cor. sys3",Systematic::Type::ENVELOPE,"_electronenergy_s3m0");
  AddSystematic("electronenergy_sys4","Roch. cor. sys4",Systematic::Type::ENVELOPE,"_electronenergy_s4m0");
  AddSystematic("electronenergy_sys5","Roch. cor. sys5",Systematic::Type::ENVELOPE,"_electronenergy_s5m0");
  AddSystematic("electronenergy_sys6","Roch. cor. sys6",Systematic::Type::ENVELOPE,"_electronenergy_s6m0");
  AddSystematic("electronenergy_sys7","Roch. cor. sys7",Systematic::Type::ENVELOPE,"_electronenergy_s7m0");
  AddSystematic("electronenergy_sys8","Roch. cor. sys8",Systematic::Type::ENVELOPE,"_electronenergy_s8m0");
  AddSystematic("electronenergy_residual","Roch. cor. residual",Systematic::Type::ENVELOPE,"_electronenergy_residual");
  AddSystematic("electronenergy","Roch. cor.",Systematic::Type::MULTI,"electronenergy_stat electronenergy_sys2 electronenergy_sys3 electronenergy_sys4 electronenergy_sys5 electronenergy_sys6 electronenergy_sys7 electronenergy_sys8 electronenergy_residual");
  AddSystematic("electronenergy_noresidual","Roch. cor.",Systematic::Type::MULTI,"electronenergy_stat electronenergy_sys2 electronenergy_sys3 electronenergy_sys4 electronenergy_sys5 electronenergy_sys6 electronenergy_sys7 electronenergy_sys8");

  for(TString era:{"2016preVFP","2016postVFP","2017","2018"}){
    AddSystematic("electronenergy_sys2_"+era,"Roch. cor. sys2",Systematic::Type::ENVELOPE,"_electronenergy_s2m0",era);
    AddSystematic("electronenergy_sys3_"+era,"Roch. cor. sys3",Systematic::Type::ENVELOPE,"_electronenergy_s3m0",era);
    AddSystematic("electronenergy_sys4_"+era,"Roch. cor. sys4",Systematic::Type::ENVELOPE,"_electronenergy_s4m0",era);
    AddSystematic("electronenergy_sys5_"+era,"Roch. cor. sys5",Systematic::Type::ENVELOPE,"_electronenergy_s5m0",era);
    AddSystematic("electronenergy_sys6_"+era,"Roch. cor. sys6",Systematic::Type::ENVELOPE,"_electronenergy_s6m0",era);
    AddSystematic("electronenergy_sys7_"+era,"Roch. cor. sys7",Systematic::Type::ENVELOPE,"_electronenergy_s7m0",era);
    AddSystematic("electronenergy_sys8_"+era,"Roch. cor. sys8",Systematic::Type::ENVELOPE,"_electronenergy_s8m0",era);
    AddSystematic("electronenergy_residual_"+era,"Roch. cor. residual",Systematic::Type::ENVELOPE,"_electronenergy_residual",era);
  }
  AddSystematic("electronenergy_era","Roch. cor.",Systematic::Type::MULTI,"electronenergy_stat electronenergy_sys2_2016preVFP electronenergy_sys3_2016preVFP electronenergy_sys4_2016preVFP electronenergy_sys5_2016preVFP electronenergy_sys6_2016preVFP electronenergy_sys7_2016preVFP electronenergy_sys8_2016preVFP electronenergy_residual_2016preVFP electronenergy_sys2_2016postVFP electronenergy_sys3_2016postVFP electronenergy_sys4_2016postVFP electronenergy_sys5_2016postVFP electronenergy_sys6_2016postVFP electronenergy_sys7_2016postVFP electronenergy_sys8_2016postVFP electronenergy_residual_2016postVFP electronenergy_sys2_2017 electronenergy_sys3_2017 electronenergy_sys4_2017 electronenergy_sys5_2017 electronenergy_sys6_2017 electronenergy_sys7_2017 electronenergy_sys8_2017 electronenergy_residual_2017 electronenergy_sys2_2018 electronenergy_sys3_2018 electronenergy_sys4_2018 electronenergy_sys5_2018 electronenergy_sys6_2018 electronenergy_sys7_2018 electronenergy_sys8_2018 electronenergy_residual_2018");

  AddSystematic("roccor_residual","Roch. cor. residual",Systematic::Type::MULTI,"muonmomentum_residual electronenergy_residual");
  AddSystematic("roccor_noresidual","Roch. cor. noresidual",Systematic::Type::MULTI,"muonmomentum_noresidual electronenergy_noresidual");
  AddSystematic("roccor","Roch. cor.",Systematic::Type::MULTI,"roccor_noresidual roccor_residual");
  

  AddSystematic("qcdss_norm_ee","SS method norm.",Systematic::Type::ENVELOPE,"scale:1.002","qcdss_ee");
  AddSystematic("qcdss_norm_ee_0bjet","SS method norm.",Systematic::Type::ENVELOPE,"scale:1.002","qcdss_ee_0bjet");
  AddSystematic("qcdss_norm_ee_nbjet","SS method norm.",Systematic::Type::ENVELOPE,"scale:1.026","qcdss_ee_nbjet");
  AddSystematic("qcdss_norm_mm","SS method norm.",Systematic::Type::ENVELOPE,"scale:1.126","qcdss_mm");
  AddSystematic("qcdss_norm_mm_0bjet","SS method norm.",Systematic::Type::ENVELOPE,"scale:1.118","qcdss_mm_0bjet");
  AddSystematic("qcdss_norm_mm_nbjet","SS method norm.",Systematic::Type::ENVELOPE,"scale:1.035","qcdss_mm_nbjet");
  AddSystematic("qcdss_norm","SS method norm.",Systematic::Type::MULTI,"qcdss_norm_ee qcdss_norm_ee_0bjet qcdss_norm_ee_nbjet qcdss_norm_mm qcdss_norm_mm_0bjet qcdss_norm_mm_nbjet");
  AddSystematic("qcdss_prompt","SS method prompt contam.",Systematic::Type::ENVELOPE,"scale:1.05","qcdss_prompt");
  AddSystematic("qcdss","SS method",Systematic::Type::MULTI,"qcdss_norm qcdss_prompt");
  AddSystematic("qcdtf_sys1","TF method sys1",Systematic::Type::ENVELOPE,"_fakeTF_up _fakeTF_down","qcdtf");
  AddSystematic("qcdtf_sys2","TF method sys2",Systematic::Type::ENVELOPE,"scale:1.3","qcdtf");
  AddSystematic("qcdtf_alt","TF method alt",Systematic::Type::ENVELOPE,"altsample:qcdss","qcdtf");
  AddSystematic("qcdtf","TF method",Systematic::Type::MULTI,"qcdtf_sys1 qcdtf_sys2");
  AddSystematic("qcdtfss","data-driven QCD est.",Systematic::Type::MULTI,"qcdss qcdtf");
  //AddSystematic("qcd","data-driven QCD est.",Systematic::Type::MULTI,"qcdtf qcdtf_alt");
  AddSystematic("qcd","data-driven QCD est.",Systematic::Type::MULTI,"qcdtf");

  AddSystematic("dyscale","DY #mu_{R}/#mu_{F}",Systematic::Type::ENVELOPE,"_scalevariation0 _scalevariation1 _scalevariation2 _scalevariation3 _scalevariation4 _scalevariation6 _scalevariation8","dy");
  AddSystematic("dymuf","DY #mu_{F}",Systematic::Type::ENVELOPE,"_scalevariation1 _scalevariation2","dy");
  AddSystematic("dymur","DY #mu_{R}",Systematic::Type::ENVELOPE,"_scalevariation3 _scalevariation6","dy");
  AddSystematic("dymurmuf","DY #mu_{R}/#mu_{F}",Systematic::Type::MULTI,"dymur dymuf");
  AddSystematic("dypdf_hessian","DY PDF hessian",Systematic::Type::HESSIAN,FormRange("_pdf%d",Range(100)),"dy");
  AddSystematic("dypdf_alphaS","DY PDF #alpha_{S}",Systematic::Type::ENVELOPE,"_alphaS_up _alphaS_down","dy");
  AddSystematic("dypdf","DY PDF",Systematic::Type::MULTI,"dypdf_hessian dypdf_alphaS");
  AddSystematic("dyisr","DY ISR",Systematic::Type::ENVELOPE,"_ISR_up _ISR_down","dy");
  AddSystematic("dyfsr","DY FSR",Systematic::Type::ENVELOPE,"_FSR_up _FSR_down","dy");
  AddSystematic("dysthw2","DY sin^{2}#theta_{W}",Systematic::Type::ENVELOPE,"_sthw2_up _sthw2_down","dy");
  AddSystematic("dylargeptscales","DY largeptscales",Systematic::Type::ENVELOPE,"_largeptscales","dy");
  AddSystematic("dyq0","DY q0",Systematic::Type::ENVELOPE,"_q0_up _q0_down","dy");
  AddSystematic("nozptweight","no DY Z p_{T} reweight",Systematic::Type::ENVELOPE,"_nozptweight","dy");
  AddSystematic("zptweight_g","DY Z p_{T} reweight (G)",Systematic::Type::ENVELOPE,"_zptweight_g","dy");
  AddSystematic("zptweight_gy","DY Z p_{T} reweight (GY)",Systematic::Type::ENVELOPE,"_zptweight_gy","dy");
  AddSystematic("zptweight_gym","DY Z p_{T} reweight (GYM)",Systematic::Type::ENVELOPE,"_zptweight_gym","dy");
  AddSystematic("zptweight","DY Z p_{T} reweight",Systematic::Type::MULTI,"nozptweight zptweight_gy zptweight_gym","dy");
  AddSystematic("noweakweight","DY Weak correction",Systematic::Type::ENVELOPE,"_noweakweight","dy");
  AddSystematic("dytheory","theory (DY)",Systematic::Type::MULTI,"dyscale dypdf zptweight noweakweight dyisr dyfsr");
  //AddSystematic("dytheory_nopdf","DY theory",Systematic::Type::MULTI,"dyalphaS dymuf dymur zptweight noweakweight dyisr dyfsr dysthw2 dylargeptscales dyq0");

  AddSystematic("ttscale","t#bar{t} #mu_{R}/#mu_{F}",Systematic::Type::ENVELOPE,"_scalevariation0 _scalevariation1 _scalevariation2 _scalevariation3 _scalevariation4 _scalevariation6 _scalevariation8","ttll");
  AddSystematic("ttmuf","t#bar{t} #mu_{F}",Systematic::Type::ENVELOPE,"_scalevariation1 _scalevariation2","ttll");
  AddSystematic("ttmur","t#bar{t} #mu_{R}",Systematic::Type::ENVELOPE,"_scalevariation3 _scalevariation6","ttll");
  AddSystematic("ttmurmuf","t#bar{t} #mu_{R}/#mu_{F}",Systematic::Type::MULTI,"ttmur ttmuf");
  AddSystematic("ttisr","t#bar{t} ISR",Systematic::Type::ENVELOPE,"_ISR_up _ISR_down","ttll");
  AddSystematic("ttfsr","t#bar{t} FSR",Systematic::Type::ENVELOPE,"_FSR_up _FSR_down","ttll");
  AddSystematic("ttpdf_hessian","t#bar{t} PDF hessian",Systematic::Type::HESSIAN,FormRange("_pdf%d",Range(100)),"ttll");
  AddSystematic("ttpdf_alphaS","t#bar{t} PDF #alpha_{S}",Systematic::Type::ENVELOPE,"_alphaS_up _alphaS_down","ttll");
  AddSystematic("ttpdf","t#bar{t} PDF",Systematic::Type::MULTI,"ttpdf_hessian ttpdf_alphaS");
  AddSystematic("notopptweight","notopptweight",Systematic::Type::ENVELOPE,"_notopptweight","tt");
  AddSystematic("tttheory","theory (t#bar{t})",Systematic::Type::MULTI,"ttscale ttisr ttfsr ttpdf notopptweight");

  AddSystematic("dytauxsec","DY tau xsec",Systematic::Type::ENVELOPE,"scale:1.018","dytau");
  AddSystematic("wjetsxsec","W xsec",Systematic::Type::ENVELOPE,"scale:1.038","wjets");
  AddSystematic("vvxsec","VV xsec",Systematic::Type::ENVELOPE,"scale:1.065","vv"); //fixme: should split vv samples
  AddSystematic("wwxsec","WW xsec",Systematic::Type::ENVELOPE,"scale:1.025","ww");
  AddSystematic("wzxsec","WZ xsec",Systematic::Type::ENVELOPE,"scale:1.061","wz");
  AddSystematic("zzxsec","ZZ xsec",Systematic::Type::ENVELOPE,"scale:1.049","zz");
  AddSystematic("ttljxsec","ttlj xsec",Systematic::Type::ENVELOPE,"scale:1.061","ttlj");
  AddSystematic("stxsec","st xsec",Systematic::Type::ENVELOPE,"scale:1.054","st");
  AddSystematic("twxsec","tw xsec",Systematic::Type::ENVELOPE,"scale:1.054","tw");
  AddSystematic("sttxsec","stt xsec",Systematic::Type::ENVELOPE,"scale:1.042","stt");
  AddSystematic("stsxsec","sts xsec",Systematic::Type::ENVELOPE,"scale:1.039","sts");
  AddSystematic("aaxsec","aa xsec",Systematic::Type::ENVELOPE,"scale:1.3","aa");
  AddSystematic("xsec","xsec",Systematic::Type::MULTI,"dytauxsec wjetsxsec wwxsec wzxsec zzxsec ttljxsec twxsec sttxsec stsxsec aaxsec");

  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/LumiRecommendationsRun2
  AddSystematic("lumi2016","lumi2016",Systematic::Type::ENVELOPE,"scale:1.01","sim&&(2016preVFP||2016postVFP)");
  AddSystematic("lumi2017","lumi2017",Systematic::Type::ENVELOPE,"scale:1.02","sim&&2017");
  AddSystematic("lumi2018","lumi2018",Systematic::Type::ENVELOPE,"scale:1.015","sim&&2018");
  AddSystematic("lumi678","lumi678",Systematic::Type::CORRELATED,"scale:1.006:sim&&(2016preVFP||2016postVFP) scale:1.009:sim&&2017 scale:1.02:sim&&2018");
  AddSystematic("lumi78","lumi78",Systematic::Type::CORRELATED,"scale:1.006:sim&&2017 scale:1.002:sim&&2018");
  AddSystematic("lumi","lumi.",Systematic::Type::MULTI,"lumi2016 lumi2017 lumi2018 lumi678 lumi78");


  AddSystematic("exp","exp. unc.",Systematic::Type::MULTI,"PUweight prefireweight z0weight btag bcharge CFSF efficiencySF qcd JEC lumi xsec roccor");
  AddSystematic("totalsys","syst. unc.",Systematic::Type::MULTI,"exp dytheory tttheory");
  AddSystematic("totalsys_more","syst. unc.",Systematic::Type::MULTI,"totalsys JES_data dymurmuf ttmurmuf dyq0 qcdtf_alt");


  AddSystematic("totalsys_detail","syst. unc.",Systematic::Type::MULTI,"PUweight prefireweight z0weight btag bcharge CFSF efficiencySF_noresidual efficiencySF_residual qcd JEC lumi xsec roccor_noresidual roccor_residual dyscale dypdf zptweight noweakweight dyisr dyfsr tttheory");

  AddSystematic("etc_0bjet","etc.",Systematic::Type::MULTI,"PUweight prefireweight z0weight btag bcharge CFSF efficiencySF_noresidual efficiencySF_residual qcd JEC lumi xsec");
  AddSystematic("totalsys_table_0bjet","syst. unc.",Systematic::Type::MULTI,"dypdf dytheory_nopdf tttheory roccor etc_0bjet");

  AddSystematic("etc_nbjet","etc.",Systematic::Type::MULTI,"PUweight prefireweight z0weight btag CFSF efficiencySF_noresidual efficiencySF_residual qcd JEC lumi xsec roccor");
  AddSystematic("totalsys_table_nbjet","syst. unc.",Systematic::Type::MULTI,"dytheory tttheory bcharge etc_nbjet");


  AddSystematic("test","totalsys",Systematic::Type::MULTI,"btag dyscale ttscale dylargeptscales");


  AddSystematic("sys_roccor_era","syst. unc.",Systematic::Type::MULTI,"PUweight prefireweight z0weight btag CFSF efficiencySF qcd JEC lumi xsec electronenergy_era muonmomentum_era");
  AddSystematic("totalsys_roccor_era","syst. unc.",Systematic::Type::MULTI,"sys_roccor_era dytheory tttheory");

  AddSystematic("sys_test","syst. unc.",Systematic::Type::MULTI,"PUweight prefireweight z0weight btag bcharge CFSF efficiencySF qcdtf JEC lumi xsec electronenergy muonmomentum");
  AddSystematic("totalsys_test","syst. unc.",Systematic::Type::MULTI,"sys_test dytheory tttheory");

  AddSystematic("sys_test2","syst. unc.",Systematic::Type::MULTI,"PUweight prefireweight z0weight btag bcharge CFSF efficiencySF qcdss JEC lumi xsec electronenergy muonmomentum");
  AddSystematic("totalsys_test2","syst. unc.",Systematic::Type::MULTI,"sys_test dytheory tttheory");

  //roccor
  AddSystematic("totalsys_roccor_detail_other","syst. unc.",Systematic::Type::MULTI,"PUweight prefireweight z0weight btag bcharge CFSF efficiencySF_noresidual efficiencySF_residual qcd JEC lumi xsec electronenergy_noresidual electronenergy_residual dyalphaS dymuf dymur dypdf zptweight noweakweight dyisr dyfsr dylargeptscales dyq0 tttheory");
  //AddSystematic("totalsys_roccor_detail","syst. unc.",Systematic::Type::MULTI,"totalsys_roccor_detail_other muonmomentum_stat muonmomentum_sys2 muonmomentum_sys3 muonmomentum_sys4 muonmomentum_sys5 muonmomentum_residual muonmomentum_sys2_2016preVFP muonmomentum_sys3_2016preVFP muonmomentum_sys4_2016preVFP muonmomentum_sys5_2016preVFP muonmomentum_residual_2016preVFP muonmomentum_sys2_2016postVFP muonmomentum_sys3_2016postVFP muonmomentum_sys4_2016postVFP muonmomentum_sys5_2016postVFP muonmomentum_residual_2016postVFP muonmomentum_sys2_2017 muonmomentum_sys3_2017 muonmomentum_sys4_2017 muonmomentum_sys5_2017 muonmomentum_residual_2017 muonmomentum_sys2_2018 muonmomentum_sys3_2018 muonmomentum_sys4_2018 muonmomentum_sys5_2018 muonmomentum_residual_2018");
  AddSystematic("totalsys_roccor_detail","syst. unc.",Systematic::Type::MULTI,"totalsys_roccor_detail_other muonmomentum_stat muonmomentum_sys2 muonmomentum_sys3 muonmomentum_sys4 muonmomentum_sys5 muonmomentum_residual_2016preVFP muonmomentum_residual_2016postVFP muonmomentum_residual_2017 muonmomentum_residual_2018");

}
#endif
