import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HttpClient } from '@angular/common/http';
import { HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import { AlertController } from 'ionic-angular';
import { NUMBER_TYPE } from '@angular/compiler/src/output/output_ast';


interface Answers_Collection {
  id : number;
  value : string;
  num : number;
}
interface Answers_Result {
  title : string;
  collection : [Answers_Collection];
  total: number;
}

@Component({
  selector: 'page-sondage-answers',
  templateUrl: 'sondage-answers.html',
})

export class SondageAnswersPage {
  uneUrl : string = "https://api.myjson.com/bins/phhb1";
  retResult : Answers_Result = null;

  constructor(public navCtrl: NavController, public navParams: NavParams,
    public httpC: HttpClient, public alertCtrl: AlertController) {
    this.setResult();
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondageAnswersPage');
  }

  setResult(){
    this.retResult = null;
    this.getResult().subscribe(res => this.retResult = res);
  }

  getResult() : Observable<Answers_Result>{
    return this.httpC.get<Answers_Result>(this.uneUrl);
  }

  convertPercentage(value, total) : string {

    var temp = (value/total) * 100;
    temp = Math.round(temp);
    return temp+"%";
  }

}
