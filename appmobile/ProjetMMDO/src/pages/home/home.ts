import { Component } from '@angular/core';
import { DetailsPage } from '../details/details';
import {HttpClient, HttpParams} from '@angular/common/http';
import { Observable } from 'rxjs/Observable';


export interface Result {
  title: string;
  author: string;
  date: number;
  image: string;
  overview : string;
}

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
  
})
export class HomePage {

  private api_key: string = 'ebb02613ce5a2ae58fde00f4db95a9c1';
  private url_base: string = 'https://api.themoviedb.org/3/search/movie';
  private url_movie: string = 'https://api.themoviedb.org/3/discover/movie'
  results: Observable<Result[]>;
  searchInput: string= "";
  date:string="2018";
  result_empty: string="Aucun Résultat";
  // Inject HttpClient into your component or service.
  constructor(private http: HttpClient) {}
  //changement de page avec paramètres
  aboutDetails=DetailsPage;
  image:string;
  url_img="https://image.tmdb.org/t/p/w500/";
  private searchEngine():Observable<Result[]>{
    // Make the HTTP request:
    return this.http.get<Result[]>(this.url_base,{
      params: new HttpParams().set('api_key',this.api_key).set('query',this.searchInput)
    }).pluck('results');
  }

private discoverMovies():Observable<Result[]>{
  // Make the HTTP request:
  return this.http.get<Result[]>(this.url_movie,{
    params: new HttpParams().set('api_key',this.api_key).set('primary_release_year',this.date)
  }).pluck('results');
}


private showRandomMovieAlert(moveis: Result[]){

}


  onInput(){
  if(!this.searchInput){
      //this.result_empty="Aucun résultat";
      this.results = this.discoverMovies();
      //this.results = Observable.of([]);
    }
  else{ 
    this.result_empty = "";
      this.results = this.searchEngine();
    }
  };
}

