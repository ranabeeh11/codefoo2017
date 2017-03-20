// chrome.exe --user-data-dir="C:/Chrome dev session" --disable-web-security

import React from 'react';
import ReactDOM from 'react-dom';
import axios from 'axios';
import _ from 'lodash';

import ItemRow from './itemRow.js'

const API_URL='http://ign-apis.herokuapp.com';

const MapData = React.createClass({
  propTypes : {
    data : React.PropTypes.object,
    limit : React.PropTypes.string,
    offset : React.PropTypes.string,
  },

  getInitialState() {
    return {
      content : [],
      contentType : this.props.contentType,//'videos',
      limit : this.props.limit,
      offset : this.props.offset,
      width: 0,
    }
  },

  componentDidMount() {
     window.addEventListener("resize", this.updateDimensions);
     this.updateDimensions();
  },

  updateDimensions() {
         this.setState({width: $(window).width()});
     },

  setContent(newContent) {
    this.setState({ content : this.state.content.concat(newContent) });
  },

  setType(newType)
  {
    this.setState({contentType : newType});
  },

  // componentWillReceiveProps(newProps)
  // {
  //     console.log(newProps);
  //     if (newProps.contentType !== this.props.contentType)
  //     {
  //       this.axiosGet(this.setContent);
  //     }
  // },

  componentWillReceiveProps(newProps) {
  if (newProps.contentType !== this.props.contentType) {
    this.setState({
       content:[],
       offset:0,
       limit:10,// whatever things need to be reset
   });
  }
},

  axiosGet(setContent) {
    //build API call
    return axios.get(`${API_URL}/${this.props.contentType}?startIndex=${this.state.offset}&count=${this.state.limit}`)
      .then(function (response) {
        console.log(response);
        setContent(response.data.data);
        return response;
      })
      .catch(function (error) {
        return error;
      });
  },

  fetchMore() {
    this.setState({
      offset : this.state.offset + this.state.limit,
    });
    this.axiosGet(this.setContent);
  },

  renderRow(record, index) {
    return <ItemRow type = {this.props.contentType} width={this.state.width} data={record} id={index} />;
  },

  render() {
    if (!this.state.content) {
      return <div>Loading ...</div>
    }
    return (
        <div className='row'>{_.map(this.state.content, this.renderRow)}
          <div className='seeMore' onClick={this.fetchMore}>See More Videos...</div>
        </div>
    );
  },
});

export default MapData;
//ReactDOM.render(<MapData />, document.getElementById('app'));
