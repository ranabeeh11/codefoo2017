import React from 'react';
import ReactDOM from 'react-dom';

const Header = React.createClass({

  render(){
    return(
      <div className="row">
        <ul className='nav nav-pills'>
          <li className='active pillHold' onClick={this.props.handleVideos}><a data-toggle='pill' className='pillStyle' href='#videos'>Videos</a></li>
          <li className='pillHold' onClick={this.props.handleArticles}><a data-toggle='pill' className='pillStyle' href='#articles'>Articles</a></li>
        </ul>
      </div>
    );
  }
});

export default Header;
