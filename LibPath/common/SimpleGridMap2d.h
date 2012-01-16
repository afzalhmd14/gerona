/**
 * @file SimpleGridMap2d.h
 * @date Jan 2012
 * @author marks
 */

#ifndef SIMPLEGRIDMAP2D_H
#define SIMPLEGRIDMAP2D_H

// C/C++
#include <stdint.h>
#include <vector>

// Project
#include "GridMap2d.h"

namespace lib_path {

/**
 * @class SimpleGridMap2d
 * @brief A simple implementation of a 2d grid map.
 */
class SimpleGridMap2d : public GridMap2d {
public:

    /**
     * @brief Create a map with the given size and resolution.
     *
     * The origin will be (0,0) and the lower threshold 0, the upper threshold 80.
     *
     * @param w Number of cells in x-direction.
     * @param h Number of cells in y-direction.
     * @param r Size of one cell in meter.
     */
    SimpleGridMap2d( const unsigned int w, const unsigned int h, const double r );

    virtual ~SimpleGridMap2d() { /* Nothing to do */ }

    /* Inherited from GridMap2d */

    inline int8_t getValue( const unsigned int x, const unsigned int y ) const
        { return data_[y*width_ + x]; }

    inline void setValue( const unsigned int x, const unsigned int y, const int8_t value )
        { data_[y*width_ + x] = value; }

    inline unsigned int getWidth() const
        { return width_; }

    inline unsigned int getHeight() const
        { return height_; }

    inline double getResolution() const
        { return res_; }

    Point2d getOrigin() const
        { return origin_; }

    inline void setOrigin( const Point2d& p )
        { origin_ = p; }

    inline bool isFree( const unsigned int x, const unsigned int y ) const {
        int8_t value = getValue( x, y );
        return value >= lowerThres_ && value <= upperThres_;
    }

    inline bool isOccupied( const unsigned int x, const unsigned int y ) const
        { return getValue( x, y ) > upperThres_; }

    inline bool isNoInformation( const unsigned int x, const unsigned int y ) const
        { return getValue( x, y ) < lowerThres_; }

    inline bool point2Cell( const Point2d& p, int& x, int& y ) const {
        if ( !isInMap( p ))
            return false;
        x = (p.x - origin_.x)/res_;
        y = (p.y - origin_.y)/res_;
        return true;
    }

    inline void cell2point( const int x, const int y, Point2d& p ) const {
        p.x = res_*(double)(x) + origin_.x + 0.5*res_;
        p.y = res_*(double)(y) + origin_.y + 0.5*res_;
    }

    inline bool isInMap( const int x, const int y ) const
        { return !(x < 0 || y < 0 || x > (int)width_ || y > (int)height_); }

    inline bool isInMap( const Point2d& p ) const {
        return (p.x - origin_.x)/res_ < width_ && (p.y - origin_.y)/res_ < height_;
    }

    /**
     * @brief Set new map data.
     * @param data The new map data. Size should be >= w * h
     * @param w New map width (number of cells in x-direction)
     * @param h new map height (number of cells in y-direction)
     */
    void set( const std::vector<int8_t>& data, const unsigned int w, const unsigned int h ) {
        width_ = w;
        height_ = h;
        data_.assign( data.begin(), data.end());
    }

protected:
    /// Number of cell in x-direction
    unsigned int width_;

    /// Number of cell in y-direction
    unsigned int height_;

    /// Size of one cell in meter
    double res_;

    /// Origin of the map
    Point2d origin_;

    /// The map data (row major order)
    std::vector<int8_t> data_;

    /// Lower threshold. Every cell with a value less than this threshold contains no information.
    int8_t lowerThres_;

    /// Upper threshold. Every cell with an value greater than this threshold is occupied.
    int8_t upperThres_;
};

} // namespace "lib_path"

#endif // SIMPLEGRIDMAP2D_H
