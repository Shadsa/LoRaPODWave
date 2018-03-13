import { Component,Injectable } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { HttpClient } from '@angular/common/http';
import { HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs/Observable';
import 'rxjs/add/operator/map';

import {SondageAnswersPage} from '../sondage-answers/sondage-answers';

interface Post {
  userId: string;
  id: string;
  title: string;
  body: string;
}

interface Result {
  name: string;
  id: number;
}

/*
Meta : string


Data : string


Result :

*/ 

const apikey = "c05e3eac979316742e075ef4ce54031a";

@Component({
  selector: 'page-sondage-question',
  templateUrl: 'sondage-question.html',
})
export class SondageQuestionPage {

  retTMDB : Result[] = [];


  constructor(public navCtrl: NavController, public navParams: NavParams,
  public httpC: HttpClient) {
    this.setList();
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad SondageQuestionPage');
  }

  setList(){
    this.getInfos().subscribe( res => this.retTMDB = res);
  }

  getInfos() : Observable<Result[]>{
    return this.httpC.get<Result[]>("https://jsonplaceholder.typicode.com/users");
  }
}
