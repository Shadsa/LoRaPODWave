import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';

@Component({
  selector: 'page-sondage-answers',
  templateUrl: 'sondage-answers.html',
})
export class SondageAnswersPage {

  constructor(public navCtrl: NavController, public navParams: NavParams) {
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondageAnswersPage');
  }

}
