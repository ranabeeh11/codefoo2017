import React from 'react';

var pattern = /[0-9]*[0-9]+:[0-9]{2}/;
var width = 0;

const ItemRow = React.createClass({
  propTypes : {
    data : React.PropTypes.shape({
      metadata : React.PropTypes.object,
    }),
  },

  getInitialState() {
    return ({
      isExpanded : false,
    });
  },

  handleExpand() {
     this.setState(prevState => ({
       isExpanded: !prevState.isExpanded
     }));
   },

   handleClick(){
     window.location = "http://www.ign.com";
   },

   componentWillReceiveProps(){
     this.setState({
       isExpanded: false,
     });
   },

  render() {
     const record = this.props.data.metadata;
     const sub = this.props.data.thumbnails;
    // //console.log(sub[1].url);
     var colon = ":";
     var saveId = this.props.id;
     saveId++;
     if(saveId < 10)
     {
       saveId = "0" + saveId;
     }
    if(record.duration >= 60)
    {
      //console.log('here');
      var minutes = Math.floor(record.duration/60);
      var seconds = (record.duration % 60);
      if(seconds < 10)
      {

        record.duration = minutes + colon + "0" + seconds;
      }
      else {
        record.duration = minutes + colon + seconds;
      }
    }
    else if(pattern.test(record.duration) == false){
      var zero = "0";
      record.duration = zero + colon + record.duration;
    }
if(this.state.isExpanded == false){
    if(this.props.type == 'videos')
    {
      return (
        <div className='row-style' onClick={this.handleExpand}>
          <div className='col-sm-2'><b className='iD'>{saveId}</b></div>
          <div className='col-sm-8'>
            <b>{record.name}</b>
            <b className='sub'>{record.description}</b>
          </div>
          <div className='col-sm-2'><b className='sub'>{record.duration}</b></div>
        </div>
     );
   }
   else {
     return(
       <div className='row-style' onClick={this.handleExpand}>
         <div className='col-sm-2'><b className='iD'>{saveId}</b></div>
         <div className='col-sm-8'>
           <b>{record.headline}</b>
           <b className='sub'>{record.subHeadline}</b>
         </div>
         <div className='col-sm-2'><b className='sub'>{record.state}</b></div>
       </div>
     );
   }
 }
 else {
    if(this.props.width > 1000)
    {
      width = 2;
    }
    else if(this.props.width > 700)
    {
      width = 1;
    }
    else {
      width = 0;
    }
   return(
      <div className = 'col-sm-8 imgHold' onClick={this.handleExpand}>
        <img className='repeat' src={sub[width].url} align='middle'></img>
        <div className='goTo' onClick={this.handleClick}>GO TO IGN</div>
      </div>
    );
 }
 },
});

export default ItemRow;
