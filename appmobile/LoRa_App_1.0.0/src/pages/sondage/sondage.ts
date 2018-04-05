import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { IonicApp } from 'ionic-angular';
import { HttpClient } from '@angular/common/http';

import {SondageAnswersPage} from '../sondage-answers/sondage-answers';
import {SondageQuestionPage} from '../sondage-question/sondage-question';

@Component({
  selector: 'page-sondage',
  templateUrl: 'sondage.html',
})

//contains the 2 others pages
export class SondagePage {

  pageAnswers : any;
  pageQuestion : any;

  constructor(public navCtrl: NavController, public navParams: NavParams, public httpc: HttpClient) {
    this.pageAnswers = SondageAnswersPage;
    this.pageQuestion = SondageQuestionPage;
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondagePage');
  }

  //the followings launch the appropriate pages
  gotoAnswers() {
    this.navCtrl.push(SondageAnswersPage);
  }

  gotoQuestion() {
    this.navCtrl.push(SondageQuestionPage);
  }

}
