import React from 'react';
import ReactDOM from 'react-dom';
import axios from 'axios';
import _ from 'lodash';
import MapData from './thisMap.js';
import Header from './thisHeader.js'

const Shell = React.createClass({
  getInitialState() {
    return(
      {
        contentType : 'videos',
        offset: 0,
        limit: 10,
      }
    );
  },

  handleVideos(){
    this.setState({contentType : 'videos', offset:0, limit: 10});
    // console.log(this.state.contentType);
  },

  handleArticles(){
    this.setState({contentType : 'articles', offset: 0, limit: 10});
    // console.log(this.state.contentType);
  },

  render(){
    return(
      <div className='container'>
        <Header handleArticles={this.handleArticles} handleVideos={this.handleVideos} />
        <MapData contentType={this.state.contentType} offset = {this.state.offset} limit = {this.state.limit}/>
      </div>
    );
  }
});


ReactDOM.render(<Shell/>, document.getElementById('app'));

/*function jsonCallback(json){
  console.log(json);
}

$.ajax({
  url: "http://run.plnkr.co/plunks/v8xyYN64V4nqCshgjKms/data-2.json",
  dataType: "jsonp"
});*/

//axios.get('http://ign-apis.herokuapp.com/articles?startIndex=30&count=5');

/*(function ($) {
    $('button').on('click', function () {
        // remove resultset if this has already been run
        $('.content ul').remove();
        // add spinner to indicate something is happening
        $('<i class="fa fa-refresh fa-spin"/>').appendTo('body');

        // get selected zip code from selectbox
        var zip = $('select option:selected').text().substring(1, 6);

        // make the AJAX request
        $.getJSON('http://data.colorado.gov/resource/4ykn-tg5h.json?entitystatus=Good%20Standing&principalzipcode=' + zip, function (data) {

            // do all this on success
            var items = [],
                $ul;

            $.each(data, function (key, val) {
                //iterate through the returned data and build a list
                items.push('<li id="' + key + '"><span class="name">' + val.entityname + '</span><br><span class="addr">' + val.principaladdress1 + '</span> <span class="city">' + val.principalcity + '</span></li>');
            });
            // if no items were returned then add a message to that effect
            if (items.length < 1) {
                items.push('<li>No results for this ZIP code, try again!</li>');
            }

            // remove spinner
            $('.fa-spin').remove();

            // append list to page
            $ul = $('<ul />').appendTo('.content');

            //append list items to list
            $ul.append(items);
        });
    });
}(jQuery));*/

/*class FetchDemo extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      posts: []
    };
  }

  componentDidMount() {
    axios.get(`http://www.reddit.com/r/${this.props.subreddit}.json`)
      .then(res => {
        const posts = res.data.data.children.map(obj => obj.data);
        this.setState({ posts });
      });
  }

  render() {
    return (
      <div>
        <h1>{`/r/${this.props.subreddit}`}</h1>
        <ul>
          {this.state.posts.map(post =>
            <li key={post.id}>{post.title}</li>
          )}
        </ul>
      </div>
    );
  }
}

ReactDOM.render(
  <FetchDemo subreddit="reactjs"/>,
  document.getElementById('app')
);*/

//ReactDOM.render(<div>hey</div>, document.getElementById('app'));
