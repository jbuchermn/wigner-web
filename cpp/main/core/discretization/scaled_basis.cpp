#include <memory>
#include <Eigen/Dense>

#include "core/discretization/scaled_basis.h"
#include "core/discretization/basis.h"

using Basis = core::discretization::Basis;


namespace core::discretization{
    
    ScaledBasis::ScaledBasis(std::shared_ptr<Basis> unscaled_, double scaled_lower_, double scaled_upper_):
        Basis(scaled_lower_, scaled_upper_, unscaled_->size, unscaled_->boundary_conditions),
        unscaled(unscaled_), unscaled_lower(unscaled_->lower), unscaled_upper(unscaled_->upper), 
        scaled_lower(scaled_lower_), scaled_upper(scaled_upper_) {}

    ScaledBasis::ScaledBasis(std::shared_ptr<Basis> unscaled_, double unscaled_lower_, double unscaled_upper_, double scaled_lower_, double scaled_upper_):
        Basis(scaled_lower_, scaled_upper_, unscaled_->size, unscaled_->boundary_conditions),
        unscaled(unscaled_), unscaled_lower(unscaled_lower_), unscaled_upper(unscaled_upper_),
        scaled_lower(scaled_upper_), scaled_upper(scaled_upper_) {}

    Eigen::VectorXcd ScaledBasis::evaluate(double x, int derivative) const{
        return std::pow(jacobian(), -derivative - .5) * unscaled->evaluate(unscale(x), derivative);
    }

    void ScaledBasis::quadrature(int order, Eigen::VectorXd& points, Eigen::VectorXd& weights) const{
        unscaled->quadrature(order, points, weights);
        for(int i=0; i<points.size(); i++) points(i) = scale(points(i));
        for(int i=0; i<weights.size(); i++) weights(i) = weights(i)*jacobian();
    }

}
