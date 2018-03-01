import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HttpClient } from '@angular/common/http';

import {SondageAnswersPage} from '../sondage-answers/sondage-answers';
import {SondageQuestionPage} from '../sondage-question/sondage-question';

@Component({
  selector: 'page-sondage',
  templateUrl: 'sondage.html',
})
export class SondagePage {

  constructor(public navCtrl: NavController, public navParams: NavParams,
              public httpc: HttpClient) {
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondagePage');
  }

  getData() {
    this.navCtrl.push(SondageQuestionPage);
  }

}
