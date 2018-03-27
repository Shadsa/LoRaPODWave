import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HttpClient, HttpParams, HttpHeaders} from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import 'rxjs/add/operator/map';
import { AlertController } from 'ionic-angular';

import {SondageAnswersPage} from '../sondage-answers/sondage-answers';

interface Question_Collection {
  id : number;
  value : string;
}
interface Question_Result {
  title : string;
  collection : [Question_Collection];
}


const httpOptions = {
  headers : new HttpHeaders({ 
    'Access-Control-Allow-Origin':'*'
  })
};


@Component({
  selector: 'page-sondage-question',
  templateUrl: 'sondage-question.html',
})

export class SondageQuestionPage {

  uneUrl : string = "https://api.myjson.com/bins/q2gph";
  urlGet : string = "http://192.168.4.1/GetPODData";
  urlPush : string = "http://192.168.4.1/GetPODData";


  retResult : Question_Result = null;

  constructor(public navCtrl: NavController, public navParams: NavParams,
  public httpC: HttpClient, public alertCtrl: AlertController) {
    this.setResult();
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondageQuestionPage');
  }

  setResult(){
    this.getResult().subscribe(res => this.retResult = res);
  }

  getResult() : Observable<Question_Result>{
    return this.httpC.get<Question_Result>(this.urlGet);
  }

  sendResult() {//TODO
    this.httpC.get<Question_Result>(this.urlGet);
  }

  buttonClicked(value, id){
    let alert = this.alertCtrl.create({
      title: 'Confirm vote',
      message: 'Do you want to vote for '+ value +'?',
      buttons: [
        {
          text: 'Cancel',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Confirm',
          handler: () => {
            console.log('Confirm '+ id +' clicked');
          }
        }
      ]
    });
    alert.present();
  }
}
